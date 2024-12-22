#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>

class State{
    private:
        int state_id;
        std::unordered_map<char, std::vector<State*>> transitions;
        std::vector<State*> e_closure;
        std::string name;
        std::set<State*> nfa_states;
        /*
            Accepting state definition, is empty if not an accepting state, else contains the name of the token
        */
        std::string acc_state_def; 
    public:
        State(int id);
        void combine_states_outputs(State* state);
        void add_nfa_state(State* nfa_state);
        std::set<char> get_transition_symbols();
        std::set<State*> get_nfa_states();
        std::unordered_map<char, std::vector<State*>> get_transitions();
        std::vector<State*> get_input_transitions(char symbol);
        void add_transition(char symbol, State* state);
        void set_transitions(std::unordered_map<char, std::vector<State*>> transitions);
        void add_e_closure(State* state);
        std::vector<State*> get_e_closure();
        void set_acc_state_def(std::string token_name);
        std::string get_acc_state_def();
        std::string get_name();
        void set_name(std::string name);
        int get_state_id();
};

#endif