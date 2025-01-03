#ifndef GRAMMARREADER_H
#define GRAMMARREADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Production.h"

#define LETF_TERM '\''
#define RIGHT_TERM '\''

#define EQUALS "::="

class GrammarReader {
public:
    GrammarReader(){};
    GrammarReader(std::string filepath);
    std::vector<Production*> getProductions();
    void displayProductions();
    std::unordered_map<std::string, Symbol*> getSymbols();
    Symbol* getStartSymbol();
private:
    int i;
    std::ifstream file;
    std::string cur_line;
    std::vector<Production*> productions;
    std::unordered_map<std::string, Symbol*> symbols;
    Symbol* start_symbol;

    void readGrammer();
    int is_special(char ch);
    std::string next_token();
    void remove_spaces();
    std::string get_word();
    Symbol* getSymbol(std::string name);
    void cleanSymbols();
};

#endif // GRAMMERREADER_H