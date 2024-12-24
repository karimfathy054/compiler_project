#include "Compiler.h"
#include "OutputHandler.h"
#include <iostream>
#include <vector>
#include "Predictive_Parser/include/FirstFollowGen.h"
#include "Predictive_Parser/include/Left_Factoring.h"
using namespace std;

int main() {
    string rules_file_path = "../bonus_test_input/lex_rules.txt";
    string grammar_file_path = "../bonus_test_input/Grammar.txt";
    string input_file_path = "../bonus_test_input/input.txt";
    Compiler compiler(rules_file_path, grammar_file_path, input_file_path);
    compiler.parse_input();
    compiler.remaining_input();
    return 0;
}