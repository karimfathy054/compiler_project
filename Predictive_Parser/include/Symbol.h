#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>

#define EPSILON "\\L"

class Production;

class Symbol
{
private:
    bool isTerminal;
    std::string name;

public:
    Symbol(std::string name);
    std::string getName();
    void setIsTerminal(bool isTerminal);
    bool getIsTerminal();
    bool isEpsilon();
};

// class Terminal:public Symbol{
//     private:
//     string name;
//     public:
//     Terminal(string name);
//     string getName();
// };

// class NonTerminal:public Symbol{
//     private:
//     vector<Production*> productions;
//     public:
//     NonTerminal();
//     void add_production(Production* production);
//     vector<Production*> getProductions();
// };

#endif