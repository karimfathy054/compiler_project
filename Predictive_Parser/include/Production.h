#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <iostream>
#include <vector>
#include "Symbol.h"

class Production {
public:
    Production(Symbol* lhs, std::vector<Symbol*> rhs);
    Symbol* getLhs();
    std::vector<Symbol*> getRhs();
    void setLhs(Symbol* lhs);
    void setRhs(std::vector<Symbol*> rhs);
    void addRhs(Symbol* rhs);
    void displayProduction();
private:
    Symbol* lhs;
    std::vector<Symbol*> rhs;
};

#endif // PRODUCTION_H