#include <iostream>
#include <bits/stdc++.h>
#include "DFA.cpp"
#include "DFAState.cpp"
using namespace std;

class DFADecoder {
public:
    // Throws runtime_error if invalid input
    string decodeDFA(DFA* dfa, string input){
        DFAState* current_state = dfa->get_start_state();
        for(int i = 0; i < input.size(); i++) {
            char symbol = input[i];
            try {
                current_state = current_state->get_input_transitions(symbol);
            } catch(const std::exception& e) {
                cout << e.what() << endl;
                return "Not DFA! Some states doesn't have transitions for some symbols";
            }
        }
        return current_state->get_top_accetping_state();
    }
};