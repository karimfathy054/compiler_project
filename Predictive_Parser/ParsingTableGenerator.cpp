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

void test1(
    unordered_map<string, Symbol*> symbols,
    vector<unordered_set<Symbol*>>& first,
    unordered_map<Symbol*, unordered_set<Symbol*>>& follow
    ) {
    // S -> R T
    first.push_back({
        symbols["s"],
        symbols["\\L"],
        symbols["v"],
        symbols["t"]
    });
    // R = s U R b
    first.push_back({
        symbols["s"]
    });
    // R = \L
    first.push_back({
        symbols["\\L"]
    });
    // U = u U
    first.push_back({
        symbols["u"]
    });
    // U = \L
    first.push_back({
        symbols["\\L"]
    });
    // V = v V
    first.push_back({
        symbols["v"]
    });
    // V = \L
    first.push_back({
        symbols["\\L"]
    });
    // T = V t T
    first.push_back({
        symbols["v"],
        symbols["t"]
    });
    // T = \L
    first.push_back({
        symbols["\\L"]
    });
    cout << "Followtin\n";
    // S
    follow[symbols["S"]] = {
        symbols["$"]
    };
    // R
    follow[symbols["R"]] = {
        symbols["v"],
        symbols["t"],
        symbols["b"],
        symbols["$"]
    };
    // U
    follow[symbols["U"]] = {
        symbols["b"],
        symbols["s"],
    };
    // V
    follow[symbols["V"]] = {
        symbols["t"]
    };
    // T
    follow[symbols["T"]] = {
        symbols["$"]
    };
}


void test2(
    unordered_map<string, Symbol*> symbols,
    vector<unordered_set<Symbol*>>& first,
    unordered_map<Symbol*, unordered_set<Symbol*>>& follow
    ) {
    // E -> T E'
    first.push_back({
        symbols["id"],
        symbols["("]
    });
    // E' -> + T E'
    first.push_back({
        symbols["+"]
    });
    // E' -> \L
    first.push_back({
        symbols["\\L"]
    });
    // T -> F T'
    first.push_back({
        symbols["id"],
        symbols["("]
    });
    // T' -> * F T'
    first.push_back({
        symbols["*"]
    });
    // T' -> \L
    first.push_back({
        symbols["\\L"]
    });
    // F -> ( E )
    first.push_back({
        symbols["("]
    });
    // F -> id
    first.push_back({
        symbols["id"]
    });
    cout << "Followtin\n";
    // E
    follow[symbols["E"]] = {
        symbols[")"],
        symbols["$"]
    };
    // E'
    follow[symbols["Ed"]] = {
        symbols[")"],
        symbols["$"]
    };
    // T
    follow[symbols["T"]] = {
        symbols["+"],
        symbols[")"],
        symbols["$"]
    };
    // T'
    follow[symbols["Td"]] = {
        symbols["+"],
        symbols[")"],
        symbols["$"]
    };
    // F
    follow[symbols["F"]] = {
        symbols["*"],
        symbols["+"],
        symbols[")"],
        symbols["$"]
    };
}

// int main() {
//     GrammarReader parser("/home/karim/compiler_project/ll_grammar.txt");
//     vector<Production*> productions = parser.getProductions();
//     cout << "Done productions\n";
//     unordered_map<string, Symbol*> symbols = parser.getSymbols();
//     symbols["$"] = new Symbol("$");

//     parser.displayProductions();

//     vector<unordered_set<Symbol*>> first;
//     unordered_map<Symbol*, unordered_set<Symbol*>> follow;

//     test2(symbols, first, follow);
    
//     cout << "Tabling...\n";
//     unordered_set<Symbol*> non_terminal_symbols;
//     for(auto &[_, symbol]: symbols) {
//         if(not symbol->getIsTerminal()) non_terminal_symbols.insert(symbol);
//     }

//     ParsingTableGenerator tableGenerator(productions, non_terminal_symbols, first, follow);

//     cout << "Displaying...\n";
//     tableGenerator.displayTable();

//     cout << "Done\n";

//     return 0;
// }
