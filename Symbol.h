#pragma once
#include <string>
#include <vector>
#define EPSILON "\L"

using namespace std;

class Production{
    private:
    string production_string;
    vector<Symbol*> production_symbols;
    public:
    Production(string production_string, vector<Symbol*> production);
    vector<Symbol*> getProduction();
    string getProductionString();
};

class Symbol{
    public:
    bool isTerminal;
    string terminal_string;
    vector<Production> productions;
    public:
    Symbol(bool isTerminal, string terminal_string);
    Symbol(vector<Production> productions);
    void addProduction(Production production);
    vector<Production> getProductions();
    bool getIsTerminal();
    string getTerminal();
    bool isEpsilon();
};

// class Terminal:public Symbol{
//     private:
//     string terminal_string;
//     public:
//     Terminal(string terminal_string);
//     string getTerminal();
// };

// class NonTerminal:public Symbol{
//     private:
//     vector<Production*> productions;
//     public:
//     NonTerminal();
//     void add_production(Production* production);
//     vector<Production*> getProductions();
// };