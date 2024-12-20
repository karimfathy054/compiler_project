#include "lexica.cpp"
#include "GrammarReader.h"
#include <iostream>
// int main()
// {
//     string input_file_path = "../../../input.txt";
//     string rules_file_path = "../../../lexical rules.txt";
//     unordered_map<string, string> symbol_table;
//     lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);
//     while (true)
//     {
//         string token = lex.next_token();
//         if (token == "%%")
//         {
//             break;
//         }
//         if (token == "whitespace")
//         {
//             continue;
//         }
//         cout << token << endl;
//     }
//     return 0;
// }

int main(){
    GrammarReader reader("/home/karim/compiler_project/Grammar.txt");
    vector<Symbol*> nonTerminals = reader.getNonTerminals();
    
    return 0;
}