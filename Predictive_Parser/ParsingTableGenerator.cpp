#include <iostream>
#include "include/ParsingTableGenerator.h"
#include "include/Production.h"
#include "include/GrammarReader.h"

using namespace std;

ParsingTableGenerator::ParsingTableGenerator(
    vector<Production*> productions, 
    std::unordered_set<Symbol*> non_terminal_symbols,
    vector<unordered_set<Symbol*>> first, 
    unordered_map<Symbol*, unordered_set<Symbol*>> follow
) {
    this->productions = productions;
    this->non_terminal_symbols = non_terminal_symbols;
    this->first = first;
    this->follow = follow;
    generateTable();
}

unordered_map<Symbol*, unordered_map<string, TableEntry*>> ParsingTableGenerator::getTable() {
    return this->table;
}

void ParsingTableGenerator::displayTable() {
    for(auto &[symbol, input_map]: table) {
       cout << "State " << symbol->getName() << endl;
       for(auto &[input, entry]: input_map) {
            cout << input << " -> Production{";
            if(entry->getIsSync()) {
                cout << "sync";
            } else{
                entry->getProduction()->displayProduction(); 
            }
            cout << "}\n";
       }
    }
}

void ParsingTableGenerator::addEntry(Symbol* nt_symbol, Symbol* input, Production* production) {
    if(table[nt_symbol].count(input->getName())) {
        throw invalid_argument("Ambigous Grammar!!!" + nt_symbol->getName() + " with input " + input->getName() + "\n");
    }
    table[nt_symbol][input->getName()] = new TableEntry(production);
}

void ParsingTableGenerator::addEntrySync(Symbol* nt_symbol, Symbol* input) {
    if(table[nt_symbol].count(input->getName())) {
        throw invalid_argument("Ambigous Grammar!!!" + nt_symbol->getName() + " with input " + input->getName() + "\n");
    }
    table[nt_symbol][input->getName()] = new TableEntry(true);
}

void ParsingTableGenerator::generateTable() {

    table.clear();

    if(first.size() != productions.size()) {
        throw invalid_argument("First set size not equal to productions size\n");
    }

    // symbols with epsilon in their first set
    unordered_set<Symbol*> symbols_to_sync(non_terminal_symbols);

    for(int i = 0; i < productions.size(); i++) {
        Production* production = productions[i];
        unordered_set<Symbol*> prod_first = first[i];
        unordered_set<Symbol*> prod_follow = follow[production->getLhs()];

        // production->displayProduction();
        // cout << endl;

        bool contains_epsilon = false;
        for(Symbol* first_symbol: prod_first) {
            if(first_symbol->isEpsilon()) {
                symbols_to_sync.erase(production->getLhs());
                contains_epsilon = true;
                for(Symbol* follow_symbol: prod_follow) {
                    addEntry(production->getLhs(), follow_symbol, production);
                }
            } else {
                addEntry(production->getLhs(), first_symbol, production);
            }
        }
    }

    for(Symbol* symbol: symbols_to_sync) {
        for(Symbol* follow_symbol: follow[symbol]) {
            addEntrySync(symbol, follow_symbol);
        }
    }
}