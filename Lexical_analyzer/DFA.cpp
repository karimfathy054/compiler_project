#pragma once

#include "NFAGenerator.cpp"
#include "RulesReader.cpp"
#include "DFAState.cpp"
#include "State.cpp"
#include <iostream>
#include <unordered_set>
#include <climits>


class DFAGenerator{
    private:
        std::string set_to_string(const std::set<State*> s) {
            std::string result = "";
            for (State* elem : s) {
                result += std::to_string(elem->get_state_id())+",";
            }
            return result;
        }
    public:
        DFAGenerator(){}
        DFAState* generateDFA(NFA* nfa, vector<pair<string, string>> rules, unordered_set<char> possible_inputs){
            int state_id_counter = 0;
            unordered_map<string, State*> dfa_states;

            State* start_state = new State(state_id_counter++);
            start_state->add_nfa_state(nfa->get_start_state());
            
            dfa_states[set_to_string(start_state->get_nfa_states())] = start_state;
            
            queue<State*> states_queue;
            states_queue.push(start_state);
            
            while(!states_queue.empty()){
                State* curr_state = states_queue.front();
                states_queue.pop();

                unordered_map<char, set<State*>> transitions;
                
                for(auto &trans: curr_state->get_transitions()) {
                    const char key = trans.first;
                    const vector<State*> states = trans.second;

                    if(transitions.find(key) == transitions.end()){
                        transitions[key] = set<State*>(states.begin(), states.end());
                    }
                    else{
                        transitions[key].insert(states.begin(), states.end());
                    }
                    // l7d hna tmam
                }

                unordered_map<char, vector<State*>> new_transitions;
                for(auto &trans: transitions){
                    set<State*> new_state_set = trans.second;
                    if(dfa_states.find(set_to_string(new_state_set)) == dfa_states.end()){
                        State* new_state = new State(state_id_counter++);
                        for(State* nfa_state: new_state_set){
                            new_state->add_nfa_state(nfa_state);
                        }
                        
                        new_transitions[trans.first] = vector<State*>{new_state};
                        
                        states_queue.push(new_state);
                        dfa_states[set_to_string(new_state_set)] = new_state;
                    }
                    else{
                        new_transitions[trans.first] = vector<State*>{dfa_states[set_to_string(new_state_set)]};
                    }
                }
                
                
                curr_state->set_transitions(new_transitions);
                int acc_state = INT_MAX;
                for(auto nfa_state: curr_state->get_nfa_states()){
                    if(nfa_state->get_acc_state_def() != ""){
                        for(int i=0; i<rules.size(); i++){
                            if(rules[i].first == nfa_state->get_acc_state_def()){
                                acc_state = min(i, acc_state);
                                break;
                            }
                        }
                    }
                }
                if(acc_state != INT_MAX){
                    curr_state->set_acc_state_def(rules[acc_state].first);
                }
            }
            return DFAState::convert_to_dfa_state(start_state, possible_inputs);
        }
};