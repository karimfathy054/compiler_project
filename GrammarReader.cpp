#include "GrammarReader.h"
#include <fstream>
#include <regex>
#include <iostream>

vector<Symbol *> GrammarReader::symbols_from_string(string s, unordered_map<string, Symbol *> &nonTerminals, unordered_map<string, Symbol *> &terminals)
{
    vector<Symbol *> symbols;
    istringstream iss(s);
    string temp;
    while (iss >> temp)
    {
        // check if the substring is enclosed in single quotes
        if (temp[0] == '\'' && temp[temp.size() - 1] == '\'')
        {
            temp = temp.substr(1, temp.size() - 2);
            if (terminals.find(temp) == terminals.end())
            {
                Symbol *sym = new Symbol(true, temp);
                terminals[temp] = sym;
                symbols.push_back(sym);
                this->terminals.push_back(sym);
            }
            else
            {
                symbols.push_back(terminals[temp]);
            }
        }
        else
        {
            if (nonTerminals.find(temp) == nonTerminals.end())
            {
                Symbol *sym = new Symbol(false, temp);
                nonTerminals[temp] = sym;
                symbols.push_back(sym);
            }
            else
            {
                symbols.push_back(nonTerminals[temp]);
            }
        }
    }
    return symbols;
}

GrammarReader::GrammarReader(string grammerFilePath)
{
    vector<string> rules;
    unordered_map<string, Symbol *> nonTerminals_map;
    unordered_map<string, Symbol *> terminals_map;
    ifstream file(grammerFilePath);
    if (file.fail())
    {
        cerr << "Error: File not found" << endl;
        return;
    }
    regex rule_start(R"((.*)# (.*))");
    regex rule_structure(R"((.*) ::= (.*))");
    string line;
    while (getline(file, line))
    {
        smatch match;
        if (regex_match(line, match, rule_start))
        {
            string old = match[1];
            string new_ = match[2];
            if (!rules.empty()) {
                string &s = rules.back();
                s += " " + old;
            }
            rules.push_back(new_);
        }
        else{
            if (!rules.empty()) {
                string &s = rules.back();
                s += " " + line;
            }
        }
    }
    file.close();
    // loop over rules and detect lhs and rhs of each rule
    for (string rule : rules)
    {
        smatch match;
        if (regex_match(rule, match, rule_structure))
        {
            string lhs = match[1];
            string rhs = match[2];
            lhs = regex_replace(lhs, regex(R"(\s+)"), " ");
            rhs = regex_replace(rhs, regex(R"(\s+)"), " ");
            // remove leading and trailing spaces
            lhs = regex_replace(lhs, regex(R"(^\s+|\s+$)"), "");
            rhs = regex_replace(rhs, regex(R"(^\s+|\s+$)"), "");

            
            Symbol *rule_nonTerminal;
            if (nonTerminals_map.find(lhs) == nonTerminals_map.end())
            {
                rule_nonTerminal = new Symbol(false, lhs);
                nonTerminals_map[lhs] = rule_nonTerminal;
            }
            else
            {
                rule_nonTerminal = nonTerminals_map[lhs];
            }
            istringstream iss(rhs);
            string temp_prod = "";
            // split rhs string on "|"
            while (getline(iss, temp_prod, '|'))
            {
                temp_prod = regex_replace(temp_prod, regex(R"(^\s+|\s+$)"), "");
                rule_nonTerminal->addProduction(Production(temp_prod, symbols_from_string(temp_prod, nonTerminals_map,terminals_map)));
            }
            this->nonTerminals.push_back(rule_nonTerminal);

            // cout << lhs << " ::= " << rhs << endl;
        }
    }
}

vector<Symbol *> GrammarReader::getNonTerminals()
{
    return this->nonTerminals;
}

vector<Symbol *> GrammarReader::getTerminals()
{
    return this->terminals;
}