#include <iostream>
#include "include/Production.h"


Production::Production(Symbol* lhs, std::vector<Symbol*> rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

Symbol* Production::getLhs() {
    return lhs;
}

std::vector<Symbol*> Production::getRhs() {
    return rhs;
}

void Production::setLhs(Symbol* lhs) {
    this->lhs = lhs;
}

void Production::setRhs(std::vector<Symbol*> rhs) {
    this->rhs = rhs;
}

void Production::addRhs(Symbol* rhs) {
    this->rhs.push_back(rhs);
}

void Production::displayProduction() {
    std::cout << lhs->getName() << " -> ";
    for (int i = 0; i < rhs.size(); i++) {
        std::cout << rhs[i]->getName() << " ";
    }
    std::cout << std::endl;
}