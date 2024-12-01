#include <iostream>
#include <bits/stdc++.h>
#include "DFAState.cpp"

using namespace std;

class DFADecoder {
    vector<pair<string, int>> tokens;
    DFAState* dfa_start_state;
    string input;
    int i;
    string extract_input(int i) {
        int prev_ind = i == 0? 0: tokens[i-1].second+1;
        return input.substr(prev_ind, tokens[i].second-prev_ind+1);
    }
public:
    DFADecoder(DFAState* dfa_start_state, string input){
        tokens = {};
        this->dfa_start_state = dfa_start_state;
        input.erase(remove(input.begin(), input.end(), '\\'), input.end());
        this->input = input;
        i = 0;
    }
    void decode_dfa(int line_number) {
        tokens = decode_dfa(0, line_number);
    }
    vector<pair<string, int>> decode_dfa(int cur_ind, int line_number){

        // holds the final accepting state and its index in the input
        vector<pair<string, int>> results;
        DFAState* current_state = dfa_start_state;

        for(int i = cur_ind; i < input.size(); i++) {
            char symbol = input[i];
            try {
                if(current_state->contains_transition(symbol)) {
                    current_state = current_state->get_transition(symbol);
                    if(current_state->get_acc_state_def() != ""){
                        results.push_back({current_state->get_acc_state_def(), i});
                    }
                }
                else{
                    cout << "Error at line " << line_number << ": Unexpected symbol " << symbol << " at index " << i << endl;
                }
            } catch(const std::exception& e) {
                throw invalid_argument("Not DFA! Some states doesn't have transitions for some symbols\n");
            }
        }

        // if no accepting state found
        if(results.size() == 0) return {};

        // if an accepting state is found at the end of the input
        if(results.back().second == input.size()-1) return {results.back()};
        
        // if some of the string is left unmatched
        // rollback if needed
        for(int i = results.size()-1; i >= 0; i--){
            vector<pair<string, int>> next_res = decode_dfa(results[i].second+1, line_number);
            if(next_res.size() >= 1){
                // this combination is valid
                next_res.insert(next_res.begin(), results[i]);
                return next_res;
            }
            // rollback
        }
        return {};
    }
    pair<string, string> next_token() {
        if(i == tokens.size()) return {"", ""};
        pair<string, string> res = {tokens[i].first, extract_input(i)};
        i++;
        return res;
    }
};