#ifndef DFASTATE_H
#define DFASTATE_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <queue>
#include "State.h"

class DFAState {
private:
    int state_id;
    std::unordered_map<char, DFAState*> transitions;
    std::string acc_state_def;
    bool isDead;
public:
    DFAState(int id);
    void combine_states_outputs(DFAState* state);
    std::set<char> get_transition_symbols();
    void set_transition(char input, DFAState* state);
    void set_acc_state_def(std::string def);
    std::string get_acc_state_def();
    std::unordered_map<char, DFAState*> get_transitions();
    DFAState* get_transition(char input);
    bool contains_transition(char input);
    int get_state_id();

    void check_all_is_dead();
    void check_is_dead();
    bool is_dead();
    void kill_state(std::unordered_set<char> possible_inputs);

    static DFAState* convert_to_dfa_state(State* start_state, std::unordered_set<char> possible_inputs){
        int state_id_counter = 0;

        DFAState* dead_state = new DFAState(-1);
        dead_state->kill_state(possible_inputs);

        // map nfa state ids to it's corresponding dfa state
        std::unordered_map<int, DFAState*> dfa_states;
        dfa_states[start_state->get_state_id()] = new DFAState(state_id_counter++);

        std::queue<std::pair<State*, DFAState*>> states_queue;
        states_queue.push({start_state, dfa_states[start_state->get_state_id()]});


        while(states_queue.size()) {
            auto [old_state, new_state] = states_queue.front();
            states_queue.pop();

            new_state->set_acc_state_def(old_state->get_acc_state_def());

            // expects to have only one transition for each input
            std::unordered_map<char, std::vector<State*>> transitions = old_state->get_transitions();
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

    static void print_dfa(std::string filename, DFAState* start_state){
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            exit(1);
        }

        std::unordered_set<int> visited;
        std::queue<DFAState*> q;
        q.push(start_state);
        while (!q.empty()) {
            DFAState* curr_state = q.front();
            q.pop();

            if (visited.find(curr_state->get_state_id()) != visited.end()) continue;
            visited.insert(curr_state->get_state_id());

            file << "State: " << curr_state->get_state_id();
            file << " Accepts: " << (curr_state->get_acc_state_def() == "" ? "NA" : curr_state->get_acc_state_def()) << std::endl;

            file << "Transition: " << std::endl;
            for (auto &[input, next] : curr_state->get_transitions()) {
                if (!next->is_dead())
                    file << input << "->" << next->get_state_id() << ' ';
                q.push(next);
            }
            file << std::endl;
        }

        file.close();
    }

};

#endif //DFASTATE_H