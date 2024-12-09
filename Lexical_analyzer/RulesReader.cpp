#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iostream>
#include <unordered_set>
#define CONCAT '~'
using namespace std;
class RulesReader
{
private:
    vector<pair<string, string>> definitions_vec;
    void process_definitions()
    {
        for (pair<string, string> definition : definitions_vec)
        {
            string name = definition.first;
            string def = definition.second;
            for (auto it = definitions.begin(); it != definitions.end(); it++)
            {
                regex r(it->first);
                def = regex_replace(def, r, it->second);
            }
            // strip white spaces from string def
            def.erase(remove(def.begin(), def.end(), ' '), def.end());
            string new_def = "";
            // precess the - operator 
            for (int i = 0; i < def.length(); i++)
            {
                if (def[i] == '-')
                {
                    new_def += '|';
                    for (int j = def[i - 1] + 1; j < def[i + 1]; j++)
                    {
                        new_def += j;
                        new_def += '|';
                    }
                }
                else
                {
                    new_def += def[i];
                }
            }
            new_def = '(' + new_def + ')';
            name = "\\b(" + name + ")\\b";
            definitions[name] = new_def;
        }
    }
    void process_rules()
    {
        for (auto &p : rules)
        {
            string &name = p.first;
            string &def = p.second;
            for (auto it = definitions.begin(); it != definitions.end(); it++)
            {
                regex r(it->first);
                def = regex_replace(def, r, it->second);
            }
            // strip white spaces from string def
            def.erase(remove(def.begin(), def.end(), ' '), def.end());
            // convert the rule to postfix
            def = convert_to_postfix(def);
        }
    }
    int precedence(char c)
    {
        if (c == '|')
        {
            return 1;
        }
        else if (c == CONCAT)
        {
            return 2;
        }
        else if (c == '*' || c == '+')
        {
            return 3;
        }
        else
        {
            return -1;
        }
    }
    string convert_to_postfix(string rule)
    {
        // precedence: | < concat < +,*
        stack<char> s;
        string postfix = "";
        bool concat = false;
        for (int i = 0; i < rule.length(); i++)
        {
            if (rule[i] == '(')
            {
                if (concat)
                {
                    while (!s.empty() && precedence(s.top()) > precedence(CONCAT))
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(CONCAT);
                }
                s.push(rule[i]);
                concat = false;
            }
            else if (rule[i] == ')')
            {
                while (s.top() != '(')
                {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
                concat = true;
            }
            else if (rule[i] == '|')
            {
                while (!s.empty() && precedence(s.top()) > precedence(rule[i]))
                {
                    postfix += s.top();
                    s.pop();
                }
                s.push(rule[i]);
                concat = false;
            }
            else if (rule[i] == '*' || rule[i] == '+')
            {
                s.push(rule[i]);
            }
            else
            {
                if (concat)
                {
                    while (!s.empty() && precedence(s.top()) > precedence(CONCAT))
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(CONCAT);
                }
                if (rule[i] == '\\')
                {
                    postfix += rule[i++];
                }
                postfix += rule[i];
                concat = true;
            }
        }
        while (!s.empty())
        {
            postfix += s.top();
            s.pop();
        }
        return postfix;
    }
    bool is_input(char c) {
        return not (c == '|' || c == '*' || c == '+' || c == '(' || c == ')' || c == CONCAT);
    }
    void generate_all_rules()
    {
        for(string k:keywords){
            all_rules.push_back ({k, k + string(k.size()-1, '~')});
        }
        for(string p:punctuations){
            if(p[0] == '\\'){
                all_rules.push_back({p.substr(1,p.size()-1), p});
            }else{
                all_rules.push_back({p, p});
            }
        }
        for (int i = 0; i < rules.size(); i++)
        {
            all_rules.push_back(rules[i]);
        }
        all_rules.push_back({"whitespace", " \n\t||+"});
    }
public:
    vector<string> keywords;
    vector<string> punctuations;
    unordered_map<string, string> definitions;
    vector<pair<string, string>> rules;
    vector<char> order;
    vector<pair<string, string>> all_rules;

    RulesReader(string rulesFilePath)
    {
        // read file and fill lists and maps
        ifstream rulesFile(rulesFilePath);
        // check for file existance
        if (!rulesFile)
        {
            cerr << "File not found" << endl;
            exit(1);
        }
        string line;
        // lines that start and end with { , } have keywords seperated with white space
        regex keywords_regex(R"(^\{\s*(.*)\s*\}$)");
        // lines that start with [ and end with ] have punctuations seperated with white space
        regex punctuations_regex(R"(^\[\s*(.*)\s*\]$)");
        // lines that have a definition have a name followed by an '=' and the definition
        regex definitions_regex(R"(^\s*(\w+)\s*=\s*(.+)\s*$)");
        // lines that have a rule have a name followed by a ':' and the rule
        regex rules_regex(R"(^\s*(\w+):\s*(.+)\s*$)");
        while (getline(rulesFile, line))
        {
            smatch match;
            if (regex_match(line, match, keywords_regex))
            {
                string keywords_line = match[1];
                istringstream iss(keywords_line);
                string keyword;
                while (iss >> keyword)
                {
                    keywords.push_back(keyword);
                    order.push_back('k');
                }
            }
            else if (regex_match(line, match, punctuations_regex))
            {
                string punctuations_line = match[1];
                istringstream iss(punctuations_line);
                string punctuation;
                while (iss >> punctuation)
                {
                    punctuations.push_back(punctuation);
                    order.push_back('p');
                }
            }
            else if (regex_match(line, match, definitions_regex))
            {
                string name = match[1];
                string def = match[2];
                definitions_vec.push_back(make_pair(name, def));
            }
            else if (regex_match(line, match, rules_regex))
            {
                string name = match[1];
                string rule = match[2];
                rules.push_back(make_pair(name, rule));
                order.push_back('r');
            }
        }
        process_definitions();
        process_rules();
        generate_all_rules();
        rulesFile.close();
    }
   
    vector<pair<string, string>> get_all_rules()
    {
        return all_rules;
    }

    unordered_set<char> get_possible_inputs() {
        unordered_set<char> possible_inputs;
        vector<pair<string, string>> rules = get_all_rules();
        for (int i = 0; i < rules.size(); i++)
        {
            string &def = rules[i].second;
            for (int j = 0; j < def.size(); j++)
            {
                if(def[j] == '\\') {
                    j++;
                    possible_inputs.insert(def[j]);
                }else if (is_input(def[j]))
                {
                    possible_inputs.insert(def[j]);
                }
            }
        }
                return possible_inputs;
    }
};

// int main()
// {
//     // stack<char> s;
//     // s.top();
//     // RulesReader r("/home/karim/compiler_project/lexical rules.txt");
//     // r.process_definitions();
//     // r.process_rules();

    // cout << "ajdgjasbjhb: " << r.rules[2].second << endl;
    // // cout<< r.convert_to_postfix("abc|klm(d|f|g)+")<<endl; //abcklmdf|g|+| output (fixed)
    // string x = r.convert_to_postfix(r.rules[2].second);
    // cout << x << endl;
    // cout << (x == "==~!=~|>|>=~|<|<=~|") << endl;
//     RulesReader r("test.txt");
//     for (auto &p : r.rules)
//     {
//         cout << p.first << ": " << p.second << endl;
//     }
//     return 0;
// }
