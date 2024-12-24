#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include <vector>
#include <unordered_map>
#include "Production.h"

class PrefixTree {
private:
    bool is_end;
    Production *production;

    std::vector<Symbol *> prefix;

    PrefixTree *parent;
    std::unordered_map<Symbol*, PrefixTree *> children;
public:
    PrefixTree(PrefixTree *parent, std::vector<Symbol*> prefix);

    std::vector<Symbol*> getPrefix();

    Production* getProduction();
    void setProduction(Production *production);

    void populate(std::vector<Production*> productions);

    void addChild(Production* production);
    std::unordered_map<Symbol*, PrefixTree *> getChildren();

    bool isEnd();
    void displayTree(int i);
    Production* leftFactor(std::vector<Production*> &new_productions);
};

#endif // PREFIXTREE_H