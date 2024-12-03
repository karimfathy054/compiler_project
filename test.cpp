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
    ifstream input_file("/home/karim/compiler_project/input.txt");
    
    // check for file existance
    if (!input_file)
    {
        cerr << "File not found" << endl;
        exit(1);
    }
    
    RulesReader r("/home/karim/compiler_project/lexical rules.txt");
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
    // dfa_gen.print_dfa(dfa_state);

    cout << "Minimizing\n";
    DFAMinimizer dfa_minimizer(dfa_state);
    dfa_minimizer.minimize();
    dfa_gen.print_dfa(dfa_state);
    cout<<"*****************************************"<<endl<<endl;

    cout << "Decoding\n";
    int line_number = 0;
    while(getline(input_file, input)) {
        line_number++;
        // cout << "Input: " << input << endl;
        if(input.size() >= 2 and input[0] == '/' and input[1] == '/') {
            // cout << "Skipping Comment\n";
            continue;
        }

        DFADecoder dfa_decoder(dfa_state, input, line_number);
        dfa_decoder.decode_dfa();

        pair<string, string> token;
        while((token = dfa_decoder.next_token()).first != "") {
            // cout << token.first << ": " << token.second << endl;
            if(token.first[0] == 'p'){
                cout << token.second << endl;
            }
            else{
                cout << token.first << endl;
            }
        }
    }    
}