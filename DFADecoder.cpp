#include <iostream>
#include <bits/stdc++.h>
#include "State.cpp"

using namespace std;

class DFADecoder {
    int cur_ind;
    State* current_state;
    string input;
public:
    DFADecoder(State* dfa_start_state, string input){
        cur_ind = 0;
        current_state = dfa_start_state;
        this->input = input;
    }
    // Throws runtime_error if invalid input
    string next_token(){
        if(cur_ind >= input.size()) throw runtime_error("End of input reached");

        // holds the final acceptin state and its index in the input
        pair<string, int> result("", -1);

        for(int i = cur_ind; i < input.size(); i++) {
            char symbol = input[i];
            try {
                current_state = current_state->get_input_transitions(symbol)[0];
            } catch(const std::exception& e) {
                throw invalid_argument("Not DFA! Some states doesn't have transitions for some symbols\n");
            }
            if(current_state->get_acc_state_def() != ""){
                result = {current_state->get_acc_state_def(), i};
            }
        }
        if(result.second == -1) throw runtime_error("omarabctarek");
        cur_ind = result.second+1;
        cout << cur_ind << endl;
        return result.first;
    }
};