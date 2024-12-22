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
        FirstFollowGen(std::vector<Production*> productions);
        void getFirstSet();
        void getFollowSet();
        void displayFirst();
        void displayFollow();
    private:
        std::vector<std::unordered_set<Symbol*>> first;
        std::unordered_map<Symbol*, std::unordered_set<Symbol*>> follow;
        std::vector<Production*> productions;
        std::unordered_set<Symbol*> computeFirstOfRhs(std::vector<Symbol*> rhs, int productionIndex);
        void computeFirstSet();
        void computeFollowSet();
};

#endif