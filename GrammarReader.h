#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Symbol.h"

using namespace std;

class GrammarReader{
    private:
    vector<Symbol*> nonTerminals;
    vector<Symbol*> terminals;
    vector<Symbol *> symbols_from_string(string s, unordered_map<string, Symbol *> &nonTerminals, unordered_map<string, Symbol *> &terminals);


    public:
    GrammarReader(string grammerFilePath); //read grammer from file and fill nonTerminals and productions
    vector<Symbol*> getNonTerminals();
    vector<Symbol*> getTerminals();
};


