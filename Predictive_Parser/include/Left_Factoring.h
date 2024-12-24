#ifndef LEFT_FACTORING_H
#define LEFT_FACTORING_H

#include "Production.h"
#include "PrefixTree.h"
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

class PrefixTree;

class Left_Factoring
{
private:
    std::unordered_map<std::string, Symbol*> symbols;
    std::unordered_map<Symbol*, std::vector<Production*>> nt_map;
    std::unordered_map<Symbol*, int> nt_count;

    std::vector<Production *> productions;
    std::vector<Production*> new_productions;

    void calculateNtMap(std::vector<Production *> productions);
    void populateSymbols(std::vector<Production *> productions);
    Symbol* getSymbol(std::string name) ;
    Symbol* makeNewName(Symbol* symbol);
    // PrefixTree *convertToPrefixTree(Production* production);
public:
    Left_Factoring(std::vector<Production *> &productions);
    void leftFactor();
    Production* factorTree(PrefixTree *tree);
    std::vector<Production*> getNewProductions();
    // void displayProductions();
};
#endif // LEFT_FACTORING_H