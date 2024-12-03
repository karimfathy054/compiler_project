#pragma once

#include <unordered_map>
#include <string>
#include <unordered_set>
#include <queue>
#include "State.cpp"

using namespace std;

class DFAState {
private:
    int state_id;
    unordered_map<char, DFAState*> transitions;
    string acc_state_def;
    bool isDead;
public:
    DFAState(int id){
        state_id = id;
        isDead = false;
        acc_state_def = "";
    }
    void combine_states_outputs(DFAState* state){
        for(auto& transition: state->get_transitions()){
            if(this->transitions.find(transition.first) != this->transitions.end()){
                this->transitions[transition.first] = transition.second;
            }
        }
    }
    set<char> get_transition_symbols(){
        set<char> symbols;
        for(auto& transition:transitions){
            symbols.insert(transition.first);
        }
        return symbols;
    }
    void set_transition(char input, DFAState* state){
        transitions[input] = state;
    }
    void set_acc_state_def(string def){
        acc_state_def = def;
    }
    string get_acc_state_def(){
        return acc_state_def;
    }
    unordered_map<char, DFAState*> get_transitions(){
        return transitions;
    }
    DFAState* get_transition(char input){
        return transitions[input];
    }
    bool contains_transition(char input){
        return transitions.find(input) != transitions.end();
    }
    int get_state_id(){
        return state_id;
    }
    
    static DFAState* convert_to_dfa_state(State* start_state, unordered_set<char> possible_inputs){
        int state_id_counter = 0;

        DFAState* dead_state = new DFAState(-1);
        dead_state->kill_state(possible_inputs);

        // map nfa state ids to it's corresponding dfa state
        unordered_map<int, DFAState*> dfa_states;
        dfa_states[start_state->get_state_id()] = new DFAState(state_id_counter++);

        queue<pair<State*, DFAState*>> states_queue;
        states_queue.push({start_state, dfa_states[start_state->get_state_id()]});


        while(states_queue.size()) {
            auto [old_state, new_state] = states_queue.front();
            states_queue.pop();

            new_state->set_acc_state_def(old_state->get_acc_state_def());

            // expects to have only one transition for each input
            unordered_map<char, vector<State*>> transitions = old_state->get_transitions();
            for(char input: possible_inputs) {
                if(not transitions.count(input)){
                    new_state->set_transition(input, dead_state);
                    continue;
                }
                State* next_state = transitions[input][0];
                if(not dfa_states.count(next_state->get_state_id())) {
                    DFAState* next_dfa_state = new DFAState(state_id_counter++);
                    states_queue.push({next_state, next_dfa_state});
                    dfa_states[next_state->get_state_id()] = next_dfa_state;
                }
                new_state->set_transition(input, dfa_states[next_state->get_state_id()]);
            }
        }
        dead_state->state_id = state_id_counter++;
        return dfa_states[start_state->get_state_id()];
    }
    

    void check_all_is_dead() {
        queue<DFAState*> q;
        unordered_set<DFAState*> visited;

        q.push(this);
        visited.insert(this);

        while(q.size()) {
            DFAState* curr_state = q.front();
            q.pop();

            curr_state->check_is_dead();

            for(auto [_, next_state]: curr_state->transitions) {
                if(visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    q.push(next_state);
                }
            }
        }
    }
    void check_is_dead(){
        isDead = false;
        for(auto [_, next_state]: transitions)
            if(next_state != this) return;
        isDead = true;
    }
    bool is_dead() {
        return isDead;
    }
    void kill_state(unordered_set<char> possible_inputs){
        for(char input: possible_inputs){
            transitions[input] = this;
        }
        isDead = true;
    }

    static void print_dfa(string filename, DFAState* start_state){
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << filename << endl;
            exit(1);
        }

        unordered_set<int> visited;
        queue<DFAState*> q;
        q.push(start_state);
        while (!q.empty()) {
            DFAState* curr_state = q.front();
            q.pop();

            if (visited.find(curr_state->get_state_id()) != visited.end()) continue;
            visited.insert(curr_state->get_state_id());

            file << "State: " << curr_state->get_state_id();
            file << " Accepts: " << (curr_state->get_acc_state_def() == "" ? "NA" : curr_state->get_acc_state_def()) << endl;

            file << "Transition: " << endl;
            for (auto &[input, next] : curr_state->get_transitions()) {
                if (!next->is_dead())
                    file << input << "->" << next->get_state_id() << ' ';
                q.push(next);
            }
            file << endl;
        }

        file.close();
    }

};