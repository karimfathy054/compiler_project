#include <iostream>
#include <bits/stdc++.h>
#include "DFAState.cpp"

using namespace std;

class DFADecoder {
    vector<pair<string, string>> tokens;
    DFAState* dfa_start_state;
    vector<string> inputs;
    string input;
    int line_number;
    int i;
private:
    vector<string> splitString(const string& str) {
        vector<string> result;
        istringstream stream(str);
        string word;

        // Read each word, skipping multiple spaces
        while (stream >> word) {
            result.push_back(word);
        }

        return result;
    }
public:
    DFADecoder(DFAState* dfa_start_state, string input, int line_number) {
        tokens = {};
        this->line_number = line_number;
        this->dfa_start_state = dfa_start_state;

        // remove the line if it's a comment
        input.erase(remove(input.begin(), input.end(), '\\'), input.end());
        this->input = input;
        // split the input into words separated by spaces
        this->inputs = splitString(input);
        i = 0;
    }
    void decode_dfa() {
        for(auto input:inputs){
            int pos = 0;
            int lastRejectedIndex = -2;
            int rejectedChars = 0;
            while(pos < input.size()) {
                string lastAcceptState = "";
                int lastAcceptIndex = pos;
                DFAState* current_state = dfa_start_state;

                for(int i=lastAcceptIndex; i<input.size(); i++){
                    if(current_state->contains_transition(input[i])){
                        current_state = current_state->get_transition(input[i]);
                        if(current_state->get_acc_state_def() != ""){
                            lastAcceptState = current_state->get_acc_state_def();
                            lastAcceptIndex = i;
                        }
                    }
                    else{
                        break;
                    }
                }
                if(lastAcceptState != ""){
                    tokens.push_back({lastAcceptState, input.substr(pos, lastAcceptIndex - pos + 1)});
                    
                    if(lastRejectedIndex != -2)
                        cout << "Invalid Token at line " << line_number << ": " << input.substr(lastRejectedIndex, rejectedChars+1) << endl;
                    lastRejectedIndex = -2;
                    rejectedChars = 0;

                    pos = lastAcceptIndex + 1;
                }
                else{
                    if(pos == lastRejectedIndex+rejectedChars+1){
                        rejectedChars++;
                    }
                    else{
                        lastRejectedIndex = pos;
                        rejectedChars = 0;
                    }
                    if(pos == input.size()-1){
                        if(lastRejectedIndex != -2)
                            cout << "Invalid Token at line " << line_number << ": " << input.substr(lastRejectedIndex, rejectedChars+1) << endl;
                        else
                            cout << "Invalid Token at line " << line_number << ": " << input.substr(pos, 1) << endl;
                    }
                    pos++;
                }
            }
        }
    }
    pair<string, string> next_token() {
        if(i == tokens.size()) return {"", ""};
        pair<string, string> res = tokens[i];
        i++;
        return res;
    }
};