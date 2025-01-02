#include "include/Left_Factoring.h"
using namespace std;

Left_Factoring::Left_Factoring(std::vector<Production *> &productions) {
    this->productions = productions;

    calculateNtMap(productions);
    populateSymbols(productions);
}

void Left_Factoring::calculateNtMap(std::vector<Production *> productions) {
    nt_map.clear();
    for(Production* p: productions) {
        nt_map[p->getLhs()].push_back(p);

        // used to make new non-terminal names after this one
        nt_count[p->getLhs()] = 0;
    }
}

void Left_Factoring::populateSymbols(std::vector<Production *> productions) {
    symbols.clear();
    for(Production* p: productions) {
        symbols[p->getLhs()->getName()] = p->getLhs();
        for(Symbol* symbol: p->getRhs()) {
            symbols[symbol->getName()] = symbol;
        }
    }
}

Symbol* Left_Factoring::getSymbol(string name) {
    if(symbols.find(name) == symbols.end()) {
        symbols[name] = new Symbol(name);
    }
    return symbols[name];
}

Symbol* Left_Factoring::makeNewName(Symbol* symbol) {
    nt_count[symbol]++;
    Symbol* s = getSymbol(symbol->getName() + '_' + to_string(nt_count[symbol]));
    s->setIsTerminal(false);
    return s;
}

std::vector<Production*> Left_Factoring::getNewProductions() {
    return new_productions;
}

std::unordered_map<std::string, Symbol*> Left_Factoring::getSymbols() {
    return symbols;
}

std::unordered_set<Symbol*> Left_Factoring::getNonTerminalSymbols() {
    unordered_set<Symbol*> non_terminals;
    for(auto &[name, sym]: symbols) {
        if(sym->getIsTerminal()){
            continue;
        }
        non_terminals.insert(sym);
    }
    return non_terminals;
}

// void Left_Factoring::displayProductions() {
//     for(auto &[symbol, productions]: new_productions) {
//         for(Production* production: productions) {
//             production->displayProduction();
//             cout << endl;
//         }
//     }
// }

void Left_Factoring::leftFactor() {
    new_productions.clear();
    
    for(auto &[symbol, nt_productions]: nt_map) {
        PrefixTree *tree = new PrefixTree(NULL, vector<Symbol*>());
        tree->populate(nt_productions);

        // cout << "NT: " << symbol->getName() << endl;
        // tree->displayTree(0);
        
        factorTree(tree);
        // new_productions.push_back(root_production);
    }

    // productions = newProductions;
}


Production* Left_Factoring::factorTree(PrefixTree *tree) {
    vector<Production*> productions_created;
    
    if(tree->isEnd()) 
        productions_created.push_back(tree->getProduction());
    
    for(auto &[symbol, child]: tree->getChildren())
        productions_created.push_back(factorTree(child));

    vector<Symbol*> prefix = tree->getPrefix();
    if(prefix.size() == 0) {
        // at root
        new_productions.insert(new_productions.end(), productions_created.begin(), productions_created.end());
        return {};
    }

    if(productions_created.size() == 1)
        return productions_created[0];



    Symbol *old_nt = getSymbol(productions_created[0]->getLhs()->getName());
    Symbol *new_nt = makeNewName(old_nt);

    prefix.push_back(new_nt);
    Production* updated_production = new Production(old_nt, prefix);
    // new_productions.push_back(updated_production);
    prefix.pop_back();

    for(Production* production: productions_created) {
        vector<Symbol*> rhs = production->getRhs();
        rhs.erase(rhs.begin(), rhs.begin() + prefix.size());

        if(rhs.size() == 0) 
            rhs.push_back(getSymbol(EPSILON));

        new_productions.push_back(new Production(new_nt, rhs));
    }

    return updated_production;
}
