#ifndef COMPILER_H
#define COMPILER_H

#include "include/GrammarReader.h"
#include "include/ParsingTableGenerator.h"
#include "include/TableEntry.h"
#include "include/lexica.h"
#include "include/LL_Grammar.h"
#include <vector>
#include <unordered_map>
#include <string>

class Compiler {
private:
    std::string rules_file_path;
    std::string grammar_file_path;
    std::string input_file_path;

    GrammarReader grammar_reader;
    std::vector<Production*> productions;
    std::unordered_map<std::string, Symbol*> symbols;
    std::unordered_set<Symbol*> non_terminal_symbols;    
    Symbol* starting_symbol;
    void read_grammar();

    // todo
    // First Follow Object
    std::vector<std::unordered_set<Symbol*>> first;
    std::unordered_map<Symbol*, std::unordered_set<Symbol*>> follow;
    void compute_first_follow_sets();

    ParsingTableGenerator table_generator;
    std::unordered_map<Symbol*, std::unordered_map<std::string, TableEntry*>> table;
    void compute_parsing_table();

    Lexical_analyzer lexical_analyzer;
    void prepare_lexical_analyzer();

    std::string next_token_wrapper();
public:
    Compiler(
        std::string rules_file_path,
        std::string grammar_file_path,
        std::string input_file_path
    );
    void parse_input();

    void remaining_input();

    void display_productions();
    void display_symbols();
    void display_table();

};


#endif // COMPILER_H