#ifndef RULESREADER_H
#define RULESREADER_H

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

class RulesReader
{
private:
    std::vector<std::pair<std::string, std::string>> definitions_vec;
    void process_definitions();
    void process_rules();
    int precedence(char c);
    std::string convert_to_postfix(std::string rule);
    bool is_input(char c);
    void generate_all_rules();
public:
    std::vector<std::string> keywords;
    std::vector<std::string> punctuations;
    std::unordered_map<std::string, std::string> definitions;
    std::vector<std::pair<std::string, std::string>> rules;
    std::vector<char> order;
    std::vector<std::pair<std::string, std::string>> all_rules;

    RulesReader(std::string rulesFilePath);
   
    std::vector<std::pair<std::string, std::string>> get_all_rules();

    std::unordered_set<char> get_possible_inputs();
};

#endif // RULESREADER_H