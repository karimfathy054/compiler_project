#include "include/Symbol.h"

using namespace std;

Symbol::Symbol(string name) {
    this->isTerminal = true;
    this->name = name;
}

void Symbol::setIsTerminal(bool isTerminal) {
    this->isTerminal = isTerminal;
}

bool Symbol::getIsTerminal(){
    return this->isTerminal;
}

void Symbol::setName(string name){
    this->name = name;
}

string Symbol::getName(){
    return this->name;
}

bool Symbol::isEpsilon(){
    return this->isTerminal && this->name == EPSILON;
}