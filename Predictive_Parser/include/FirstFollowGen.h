#ifndef FIRSTFOLLOW_H
#define FIRSTFOLLOW_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Symbol.h"
#include "Production.h"

class FirstFollowGen {
    public:
        FirstFollowGen(std::vector<Production*> productions, Symbol* startSymbol);
        std::vector<std::unordered_set<Symbol*>> getFirst();
        std::unordered_map<Symbol*, std::unordered_set<Symbol*>> getFollow();
        std::unordered_set<Symbol*> getFollowSetForSymbol(Symbol* symbol);
        std::unordered_set<Symbol*> getFirstSetForSymbol(Symbol* symbol);
        void displayFirst();
        void displayFollow();

    private:
        std::vector<std::unordered_set<Symbol*>> first;
        std::unordered_map<Symbol*, std::unordered_set<Symbol*>> follow;
        std::vector<Production*> productions;
        Symbol* startSymbol;
        std::unordered_set<Symbol*> computeFirstOfRhs(std::vector<Symbol*> rhs);
        void computeFirstSet();
        void computeFollowSet();
};
#endif