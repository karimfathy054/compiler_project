#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include "DFAState.cpp"

using namespace std;

class DFADecoder {
private:
    DFAState* dfa_start_state;
    string input;
    int line_number;
    int i;
    public:
    DFADecoder(DFAState* dfa_start_state, string input, int line_number) {
        this->line_number = line_number;
        this->dfa_start_state = dfa_start_state;
        
        this->input = input;
        i = 0;
    }
    pair<string, string> next_token() {
        if(i > input.size()) return {"", ""};
        if(i == input.size()) {
            // handle if a state accepts \L
            i++;
            if(dfa_start_state->get_acc_state_def() != "")
                return {dfa_start_state->get_acc_state_def(), ""};
            // if no state accepts \L
            return {"", ""};
        }

        int last_accept_index = -1;
        string last_accept_state = "";
        DFAState* current_state = dfa_start_state;

        for(int ind = i; ind < input.size(); ind++) {
            if(current_state->is_dead()) break;

            if(current_state->contains_transition(input[ind])) {
                current_state = current_state->get_transition(input[ind]);

                if(current_state->get_acc_state_def() != "") {
                    last_accept_state = current_state->get_acc_state_def();
                    last_accept_index = ind;
                }
            }
            else{
                // throw the error message
                throw invalid_argument("Invalid Token at line " + to_string(line_number) + ":" + to_string(ind) + ": " + input.substr(ind));
            }
        }
        
        // no accepting state found
        if (last_accept_index == -1)
            throw invalid_argument("Invalid Token at line " + to_string(line_number) + ":" + to_string(i) + ": " + input.substr(i));

        string matched_input = input.substr(i, last_accept_index - i + 1);
        i = last_accept_index + 1;

        return {last_accept_state, matched_input};
    }
};