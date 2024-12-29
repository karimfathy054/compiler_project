#include "Compiler.h"
#include <iostream>
#include <vector>
#include "Predictive_Parser/include/FirstFollowGen.h"
using namespace std;

int main() {
    string rules_file_path = "../bonus_test_input/lex_rules.txt";
    string grammar_file_path = "../bonus_test_input/Grammar.txt";
    string input_file_path = "../bonus_test_input/input.txt";
    Compiler compiler(rules_file_path, grammar_file_path, input_file_path, "../output.md");
    compiler.parse_input();
    compiler.remaining_input();
    return 0;
}