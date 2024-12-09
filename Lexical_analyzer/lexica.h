#ifndef LEX_H
#define LEX_H
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "DFA.cpp"

using namespace std;
class lexical_analyzer
{
private:
    string rules_file_path;
    string input_file_path;
    ifstream input_file;
    DFAState *dfa_start_state;
    unordered_map<string, string> *symbol_table;

    void prepare_dfa(std::string &rules_file_path);

public:
    lexical_analyzer(string rules_file_path, string input_file_path, unordered_map<string, string> *symbol_table);
    string next_token();
};
#endif // LEX_H