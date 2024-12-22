#include "include/DFAState.h"

using namespace std;

DFAState::DFAState(int id){
    state_id = id;
    isDead = false;
    acc_state_def = "";
}

void DFAState::combine_states_outputs(DFAState* state){
    for(auto& transition: state->get_transitions()){
        if(this->transitions.find(transition.first) != this->transitions.end()){
            this->transitions[transition.first] = transition.second;
        }
    }
}

set<char> DFAState::get_transition_symbols(){
    set<char> symbols;
    for(auto& transition:transitions){
        symbols.insert(transition.first);
    }
    return symbols;
}

void DFAState::set_transition(char input, DFAState* state){
    transitions[input] = state;
}

void DFAState::set_acc_state_def(string def){
    acc_state_def = def;
}

string DFAState::get_acc_state_def(){
    return acc_state_def;
}

unordered_map<char, DFAState*> DFAState::get_transitions(){
    return transitions;
}

DFAState* DFAState::get_transition(char input){
    return transitions[input];
}

bool DFAState::contains_transition(char input){
    return transitions.find(input) != transitions.end();
}

int DFAState::get_state_id(){
    return state_id;
}

void DFAState::check_all_is_dead() {
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

void DFAState::check_is_dead(){
    isDead = false;
    for(auto [_, next_state]: transitions)
        if(next_state != this) return;
    isDead = true;
}

bool DFAState::is_dead() {
    return isDead;
}

void DFAState::kill_state(unordered_set<char> possible_inputs){
    for(char input: possible_inputs){
        transitions[input] = this;
    }
    isDead = true;
}