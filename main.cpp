#include "Utils/include/Compiler.h"
#include "Utils/include/OutputHandler.h"
#include <iostream>
#include <vector>
#include "Predictive_Parser/include/FirstFollowGen.h"
#include "Predictive_Parser/include/Left_Factoring.h"
using namespace std;

int main() {
    string rules_file_path = "../Tests/report input/lexical rules.txt";
    string grammar_file_path = "../Tests/report input/Grammar.txt";
    string input_file_path = "../Tests/report input/input.txt";
    Compiler compiler(rules_file_path, grammar_file_path, input_file_path);
    compiler.parse_input();
    compiler.remaining_input();
    return 0;
}