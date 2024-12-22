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

// using namespace std;

class FirstFollowGen {
    public:
        FirstFollowGen(std::vector<Production*> productions);
        void getFirst();
        void getFollow();
        void displayFirst();
        void displayFollow();
    private:
        std::unordered_map<Symbol*, std::unordered_set<Symbol*>> first;
        std::vector<Production*> productions;
        void computeFirst();
        std::unordered_set<Symbol*> computeFirstOfRhs(std::vector<Symbol*> rhs);
};

#endif