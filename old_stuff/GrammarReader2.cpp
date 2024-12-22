// #include "include/GrammarReader.h"
// #include "include/Symbol.h"
// #include <fstream>
// #include <regex>
// #include <iostream>

// using namespace std;

// vector<Symbol *> symbols_from_string(string s, unordered_map<string, Symbol *> &sym_map)
// {
//     vector<Symbol *> symbols;
//     istringstream iss(s);
//     string temp;
//     while (iss >> temp)
//     {
//         // check if the substring is enclosed in single quotes
//         if (temp[0] == '\'' && temp[temp.size() - 1] == '\'')
//         {
//             temp = temp.substr(1, temp.size() - 2);
//             if (sym_map.find(temp) == sym_map.end())
//             {
//                 Symbol *sym = new Symbol(temp);
//                 sym->setIsTerminal(true);
//                 sym_map[temp] = sym;
//                 if(sym->isEpsilon()){
//                     continue;
//                 }
//                 symbols.push_back(sym);
//             }
//             else
//             {
//                 if(sym_map[temp]->isEpsilon()){
//                     continue;
//                 }
//                 symbols.push_back(sym_map[temp]);
//             }
//         }
//         else
//         {
//             if (sym_map.find(temp) == sym_map.end())
//             {
//                 Symbol *sym = new Symbol(temp);
//                 sym->setIsTerminal(false);
//                 sym_map[temp] = sym;
//                 symbols.push_back(sym);
//             }
//             else
//             {
//                 symbols.push_back(sym_map[temp]);
//             }
//         }
//     }
//     return symbols;
// }

// GrammarReader::GrammarReader(string filepath)
// {
//     vector<string> rules;
//     unordered_map<string, Symbol *> terminals_map;
//     ifstream file(filepath);
//     if (file.fail())
//     {
//         cerr << "Error: File not found" << endl;
//         return;
//     }
//     regex rule_start(R"((.*)# (.*))");
//     regex rule_structure(R"((.*) ::= (.*))");
//     string line;
//     while (getline(file, line))
//     {
//         smatch match;
//         if (regex_match(line, match, rule_start))
//         {
//             string old = match[1];
//             string new_ = match[2];
//             if (!rules.empty()) {
//                 string &s = rules.back();
//                 s += " " + old;
//             }
//             rules.push_back(new_);
//         }
//         else{
//             if (!rules.empty()) {
//                 string &s = rules.back();
//                 s += " " + line;
//             }
//         }
//     }
//     file.close();
//     // loop over rules and detect lhs and rhs of each rule
//     for (string rule : rules)
//     {
//         smatch match;
//         if (regex_match(rule, match, rule_structure))
//         {
//             string lhs = match[1];
//             string rhs = match[2];
//             lhs = regex_replace(lhs, regex(R"(\s+)"), " ");
//             rhs = regex_replace(rhs, regex(R"(\s+)"), " ");
//             // remove leading and trailing spaces
//             lhs = regex_replace(lhs, regex(R"(^\s+|\s+$)"), "");
//             rhs = regex_replace(rhs, regex(R"(^\s+|\s+$)"), "");

            
//             Symbol *rule_nonTerminal;
//             if (symbols.find(lhs) == symbols.end())
//             {
//                 rule_nonTerminal = new Symbol(lhs);
//                 rule_nonTerminal->setIsTerminal(false);
//                 symbols[lhs] = rule_nonTerminal;
//             }
//             else
//             {
//                 rule_nonTerminal = symbols[lhs];
//             }
//             istringstream iss(rhs);
//             string temp_prod = "";
//             // split rhs string on "|"
//             while (getline(iss, temp_prod, '|'))
//             {
//                 temp_prod = regex_replace(temp_prod, regex(R"(^\s+|\s+$)"), "");
//                 this->productions.push_back(new Production(rule_nonTerminal, symbols_from_string(temp_prod, this->symbols)));
//             }
//         }
//     }
// }

// vector<Production*> GrammarReader::getProductions(){
//     return this->productions;
// }

// void GrammarReader::displayProductions(){
//     for(Production* p : this->productions){
//         p->displayProduction();
//     }
// }

// unordered_map<string, Symbol*> GrammarReader::getSymbols(){
//     return this->symbols;
// }

