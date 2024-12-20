#include "include/Production.h"


Production::Production(std::string lhs, std::vector<std::string> rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

std::string Production::getLhs() {
    return lhs;
}

std::vector<std::string> Production::getRhs() {
    return rhs;
}

void Production::setLhs(std::string lhs) {
    this->lhs = lhs;
}

void Production::setRhs(std::vector<std::string> rhs) {
    this->rhs = rhs;
}

void Production::addRhs(std::string rhs) {
    this->rhs.push_back(rhs);
}