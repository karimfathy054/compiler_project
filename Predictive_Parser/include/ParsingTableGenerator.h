#ifndef PARSINGTABLEGENERATOR_H
#define PARSINGTABLEGENERATOR_H

#include <unordered_map>
#include <unordered_set>
#include "TableEntry.h"


class ParsingTableGenerator {
public:
    ParsingTableGenerator(){};
    ParsingTableGenerator(
        std::vector<Production*> productions, 
        std::unordered_set<Symbol*> non_terminal_symbols,
        std::vector<std::unordered_set<Symbol*>> first, 
        std::unordered_map<Symbol*, std::unordered_set<Symbol*>> follow
    );
    std::unordered_map<Symbol*, std::unordered_map<std::string, TableEntry*>> getTable();
    void displayTable();
private:
    std::vector<Production*> productions;
    std::unordered_map<Symbol*, std::unordered_map<std::string, TableEntry*>> table;
    std::unordered_set<Symbol*> non_terminal_symbols;
    std::vector<std::unordered_set<Symbol*>> first;
    std::unordered_map<Symbol*, std::unordered_set<Symbol*>> follow;
    void generateTable();
    void addEntry(Symbol* nt_symbol, Symbol* input, Production* production);
    void addEntrySync(Symbol* nt_symbol, Symbol* input);
};

#endif