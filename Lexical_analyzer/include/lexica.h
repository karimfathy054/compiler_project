#ifndef LEX_H
#define LEX_H

#define END_OF_INPUT "$"

#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "RulesReader.h"
#include "NFAGenerator.h"
#include "DFAMinimizerPartitioning.h"
#include "DFAGenerator.h"

class Lexical_analyzer
{
private:
    std::string rules_file_path;
    std::string input_file_path;
    std::ifstream input_file;
    DFAState *dfa_start_state;
    std::unordered_map<std::string, std::string> *symbol_table;
    std::string prev;

    void prepare_dfa(std::string &rules_file_path);

public:
    Lexical_analyzer(){};
    Lexical_analyzer(std::string &rules_file_path, std::string &input_file_path);
    std::string next_token();
    std::unordered_map<std::string, std::string> get_symbol_table();
};
#endif // LEX_H