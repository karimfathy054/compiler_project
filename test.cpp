#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "DFA.cpp"
#include "DFADecoder.cpp"
#include "DFAMinimizer.cpp"

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
    cout << "Rules: \n";
    for(auto rule: rules) {
        cout << rule.first << ": " << rule.second << endl;
    }
    cout << "NFA\n";
    NFAGenerator nfa_gen;
    NFA* nfa = nfa_gen.generateNFA(rules);
    cout << "DFA\n";
    DFAGenerator dfa_gen;
    cout << "Generating\n";
    DFAState* dfa_state = dfa_gen.generateDFA(nfa, rules, r.get_possible_inputs());
    cout << "Minimized DFA\n";
    DFAMinimizer dfa_minimizer(dfa_state);
    cout << "Minimizing\n";
    dfa_minimizer.minimize();
    cout << "Decoding\n";
    DFADecoder dfa_decoder(dfa_state, input);
    cout << "Decoding dga\n";
    dfa_decoder.decode_dfa();


    cout << "Tokens: \n";
    pair<string, string> token;
    while((token = dfa_decoder.next_token()).first != "") {
        cout << "Token: " << token.first << " Value: " << token.second << endl;
    }
}