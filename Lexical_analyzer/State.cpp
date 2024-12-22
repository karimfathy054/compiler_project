#include "include/State.h"

using namespace std;

State::State(int id){
    state_id = id;
    acc_state_def = "";
}
void State::combine_states_outputs(State* state){
    for(auto& transition:state->get_transitions()){
        for(auto& transition: state->get_transitions()){
            if(this->transitions.find(transition.first) != this->transitions.end()){
                this->transitions[transition.first] = transition.second;
            }
        }
    }
}
void State::add_nfa_state(State* nfa_state){
    nfa_states.insert(nfa_state);
    for(auto &trans: nfa_state->get_transitions()){
        if(transitions.find(trans.first) != transitions.end()){
            transitions[trans.first].insert(transitions[trans.first].end(), trans.second.begin(), trans.second.end());
        }
        else{
            transitions[trans.first] =  trans.second;
        }
    }
    vector<State*> e_closure = nfa_state->get_e_closure();
    int i = 0;
    while(i<e_closure.size()){
        State* curr_nfa_state = e_closure[i];
        nfa_states.insert(curr_nfa_state);
        for(auto &trans: curr_nfa_state->get_transitions()){
            if(transitions.find(trans.first) != transitions.end()){
                transitions[trans.first].insert(transitions[trans.first].end(), trans.second.begin(), trans.second.end());
            }
            else{
                transitions[trans.first] = trans.second;
            }
        }
        for(State* e_closure_state : curr_nfa_state->get_e_closure()){
            if(nfa_states.find(e_closure_state) == nfa_states.end()) {
                nfa_states.insert(e_closure_state);
                e_closure.push_back(e_closure_state);
            }
        }
        i++;
    }
}
set<char> State::get_transition_symbols(){
    set<char> symbols;
    for(auto& transition:transitions){
        symbols.insert(transition.first);
    }
    return symbols;
}
set<State*> State::get_nfa_states(){
    return nfa_states;
}
unordered_map<char, vector<State*>> State::get_transitions(){
    return transitions;
}
vector<State*> State::get_input_transitions(char symbol){
    if (transitions.find(symbol) == transitions.end()) {
        throw std::runtime_error("No more transitions exist");
    }
    return transitions[symbol];
}
void State::add_transition(char symbol, State* state){
    transitions[symbol].push_back(state);
}
void State::set_transitions(unordered_map<char, vector<State*>> transitions){
    this->transitions = transitions;
}
void State::add_e_closure(State* state){
    e_closure.push_back(state);
}
vector<State*> State::get_e_closure(){
    return e_closure;
}
void State::set_acc_state_def(string token_name){
    acc_state_def = token_name;
}
string State::get_acc_state_def(){
    return acc_state_def;
}
string State::get_name(){
    return name;
}
void State::set_name(string name){
    this->name = name;
}
int State::get_state_id(){
    return state_id;
}