#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iostream>
using namespace std;
class RulesReader
{
    // TODO: this class should read the rules from a file and provide them in postfix formate for easy decoding
    public:
        vector<string> keywords; 
        vector<string> punctuations; 
        unordered_map<string,string> definitions; 
        vector<pair<string,string>> definitions_vec;
        vector<pair<string, string>> rules; 
        
    RulesReader(string rulesFilePath)
    {
        // read file and fill lists and maps
        ifstream rulesFile(rulesFilePath);
        string line;
        // lines that start and end with { , } have keywords seperated with white space
        regex keywords_regex(R"(^\{\s*(.*)\s*\}$)");
        // lines that start with [ and end with ] have punctuations seperated with white space
        regex punctuations_regex(R"(^\[\s*(.*)\s*\]$)");
        // lines that have a definition have a name followed by a white space and the definition
        regex definitions_regex(R"(^\s*(\w+)\s*=\s*(.+)\s*$)");
        // lines that have a rule have a name followed by a white space and the rule
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
                }
                
            }
            else if (regex_match(line, match, punctuations_regex))
            {
                string punctuations_line = match[1];
                istringstream iss(punctuations_line);
                string punctuation;
                while (iss>>punctuation)
                {
                    punctuations.push_back(punctuation);
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
            }
        }
    }
    void process_definitions(){
        for(pair<string,string> definition: definitions_vec){
            string name = definition.first;
            string def = definition.second;
            for(auto it = definitions.begin(); it != definitions.end(); it++){
                regex r (it->first);
                def = regex_replace(def, r, it->second);
            }
            // strip white spaces from string def
            def.erase(remove(def.begin(), def.end(), ' '), def.end());
            string new_def = "";
            // precess the - operator as a for loop for all charachters between the prev and the next charachter in ascii and insert '|' between them
            for(int i = 0; i < def.length(); i++){
                if(def[i] == '-'){
                        new_def += '|';
                    for(int j = def[i-1]+1; j < def[i+1]; j++){
                        new_def += j;
                        new_def += '|';
                    }
                } else {
                    new_def += def[i];
                }
            }
            new_def = '(' + new_def + ')';
            name = "\\b(" + name + ")\\b";
            definitions[name] = new_def;
        }
    }
    void process_rules(){
        // vector<pair<string,string>> processed_rules;
        // loop through all references of rule pairs

        for(auto& p: rules){
            string& name = p.first;
            string& def = p.second;
            for(auto it = definitions.begin(); it != definitions.end(); it++){
                regex r(it->first);
                def = regex_replace(def, r, it->second);
            }
            // strip white spaces from string def
            def.erase(remove(def.begin(), def.end(), ' '), def.end());
            // convert the rule to postfix
            // processed_rules.push_back(make_pair(name, convert_to_postfix(def)));
        }
        // rules = processed_rules;
    }
    // TODO: implement this function correctly
    int precedence(char c){
        if(c == '|'){
            return 1;
        } else if(c == '*' || c == '+'){
            return 2;
        } else {
            return -1;
        }
    }
    string convert_to_postfix(string rule){
        // convert the rule to postfix
        // precedence: | < concat < +,*

        stack<char> s;
        string postfix = "";
        for(int i = 0; i < rule.length(); i++){
            if(rule[i] == '('){
                s.push(rule[i]);
            } else if(rule[i] == ')'){
                while(s.top() != '('){
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
            } else if(rule[i] == '|'){
                while(!s.empty() && precedence(s.top()) >= precedence(rule[i])){
                    postfix += s.top();
                    s.pop();
                }
                s.push(rule[i]);
            }else if (rule[i] == '*' || rule[i] == '+'){
                s.push(rule[i]);
            }
            // ! how to represent concat??
            // ! what to do with '\'
            // ? relop: \=\= | !\= | > | >\= | < | <\=
            else {
                postfix += rule[i];
            }
        }
        while(!s.empty()){
            postfix += s.top();
            s.pop();
        }
        return postfix;
    }
    
};

int main(){
    stack<char> s;
    s.top();
    RulesReader r("/home/karim/compiler_project/lexical rules.txt");
    cout<< r.convert_to_postfix("abc|klm(d|f|g)+")<<endl; //abcklmdf|g|+|
    r.process_definitions();
    r.process_rules();
    return 0;
}