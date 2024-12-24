#include "include/PrefixTree.h"

using namespace std;

PrefixTree::PrefixTree(PrefixTree *parent, vector<Symbol*> prefix) { 
    this->parent = parent;
    this->is_end = false;
    this->prefix = prefix;
}

vector<Symbol*> PrefixTree::getPrefix() {
    return prefix;
}

void PrefixTree::populate(vector<Production*> productions) {
    for(Production* production: productions) {
        addChild(production);
    }
}

Production* PrefixTree::getProduction() { 
    // only valid when isEnd() is true
    return production;
}

void PrefixTree::setProduction(Production *production) { 
    this->production = production;
    this->is_end = true;
};

void PrefixTree::addChild(Production *production) {
    vector<Symbol*> rhs = production->getRhs();
    PrefixTree *current = this;
    // vector<Symbol*> prefix = this->prefix;

    for(Symbol* symbol: rhs) {
        if(not current->children.count(symbol)) {
            current->prefix.push_back(symbol);
            PrefixTree *child = new PrefixTree(current, vector(current->prefix));
            current->prefix.pop_back();
            current->children[symbol] = child;
        }
        current = current->children[symbol];
    }

    current->setProduction(production);
}

std::unordered_map<Symbol*, PrefixTree *> PrefixTree::getChildren() {
    return children;
}

bool PrefixTree::isEnd() {
    return is_end;
}

void PrefixTree::displayTree(int i) {
    cout << "In " << i  << endl;
    for(auto &[symbol, child]: children) {
        cout << symbol->getName() << endl;
        child->displayTree(i+1);
    }
    cout << "Out " << i << endl;
}


Production* PrefixTree::leftFactor(vector<Production*> &new_productions) {
}

