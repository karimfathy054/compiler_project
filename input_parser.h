#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H
#include "include/GrammerReader.h"
#include "include/TableEntry.h"
#include "lexica.h"
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

string next_token_wrapper(lexical_analyzer &lex);

void parse_input(string input_file_path, lexical_analyzer &lex ,unordered_map<Symbol*,unordered_map<string, TableEntry>> predictive_parsing_table,Symbol* starting_symbol);

#endif // INPUT_PARSER_H