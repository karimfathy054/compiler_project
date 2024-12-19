#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

using namespace std;

class GrammerReader{
    private:
    vector<Symbol*> nonTerminals;
    vector<vector<Symbol*>*> productions;
    public:
    GrammerReader(string grammerFilePath); //read grammer from file and fill nonTerminals and productions
    vector<Symbol*> getNonTerminals();
    vector<vector<Symbol*>*> getProductions();
};


