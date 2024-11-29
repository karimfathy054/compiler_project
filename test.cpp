#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "DFA.cpp"
#include "DFADecoder.cpp"

// Test the lexical analyzer using the rules in the file "test.txt"
// this example from Lecture 4 (Dr pdfs) 
int main(int, char**){
    string input;
    ifstream input_file("../input.txt");
    getline(input_file, input);

    // check for file existance
    if (!input_file)
    {
        cerr << "File not found" << endl;
        exit(1);
    }
    
    RulesReader r("../test.txt");
    auto rules = r.get_all_rules();

    NFAGenerator nfa_gen;
    NFA* nfa = nfa_gen.generateNFA(rules);

    DFAGenerator dfa_gen;
    DFAState* dfa_state = dfa_gen.generateDFA(nfa, rules, r.get_possible_inputs());


    DFADecoder dfa_decoder(dfa_state, input);
    dfa_decoder.decode_dfa();


    cout << "Tokens: \n";
    pair<string, string> token;
    while((token = dfa_decoder.next_token()).first != "") {
        cout << "Token: " << token.first << " Value: " << token.second << endl;
    }
}