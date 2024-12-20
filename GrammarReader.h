#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

using namespace std;

class GrammarReader{
    private:
    vector<Symbol*> nonTerminals;
    public:
    GrammarReader(string grammerFilePath); //read grammer from file and fill nonTerminals and productions
    vector<Symbol*> getNonTerminals();
};


