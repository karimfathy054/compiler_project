#include "Symbol.h"

Symbol::Symbol(bool isTerminal, string terminal_string){
    this->isTerminal = isTerminal;
    this->terminal_string = terminal_string;
}

Symbol::Symbol(vector<Production> productions){
    this->productions = productions;
    this->isTerminal = false;
}

vector<Production> Symbol::getProductions(){
    if(this->isTerminal){
        throw "Symbol is terminal";
    }
    return this->productions;
}

bool Symbol::getIsTerminal(){
    return this->isTerminal;
}

string Symbol::getTerminal(){
    if(!this->isTerminal){
        throw "Symbol is not terminal";
    }
    return this->terminal_string;
}

void Symbol::addProduction(Production production){
    this->productions.push_back(production);
}

bool Symbol::isEpsilon(){
    return this->isTerminal && this->terminal_string == EPSILON;
}

Production::Production(string production_string, vector<Symbol*> production){
    this->production_string = production_string;
    this->production_symbols = production;
}

vector<Symbol*> Production::getProduction(){
    return this->production_symbols;
}

string Production::getProductionString(){
    return this->production_string;
}


