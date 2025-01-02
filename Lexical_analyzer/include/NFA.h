#ifndef NFA_H
#define NFA_H

#include "State.h"

class NFA{
    private:
        static int state_id_counter; 
        State* start_state;
        State* final_state;
    public:
        NFA();
        NFA(char c);
        NFA(State* start_state, State* final_state);

        void mark_accepting(std::string token_name);
        State* get_start_state();
        State* get_final_state();

        static void reset_state_id_counter(){
            state_id_counter = 0;
        }
        static NFA* concatenate(NFA* nfa1, NFA* nfa2){
            nfa1->final_state->add_e_closure(nfa2->start_state);
            nfa1->final_state = nfa2->final_state;
            return nfa1; //could return the modified nfa1 instead of new nfa objects ( i don't know the effect of adding more new objects but i guess it won't be efficient)
        }
        static NFA* union_(NFA* nfa1, NFA* nfa2){
            State* new_start = new State(state_id_counter++);
            new_start->add_e_closure(nfa1->start_state);
            new_start->add_e_closure(nfa2->start_state);
            State* new_final = new State(state_id_counter++);
            nfa1->final_state->add_e_closure(new_final);
            nfa2->final_state->add_e_closure(new_final);
            return new NFA(new_start, new_final);
        }
        static NFA* union_(std::vector<NFA*> nfas){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            for(auto &nfa : nfas){
                new_start->add_e_closure(nfa->start_state);
                nfa->final_state->add_e_closure(new_final);
            }
            return new NFA(new_start, new_final);
        }
        static NFA* union_front(std::vector<NFA*> nfas){
            State* new_start = new State(state_id_counter++);
            for(auto& nfa: nfas){
                new_start->add_e_closure(nfa->start_state);
            }
            return new NFA(new_start, nullptr);
        }
        static NFA* kleene_closure(NFA* nfa){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            new_start->add_e_closure(new_final);
            new_start->add_e_closure(nfa->start_state);
            nfa->final_state->add_e_closure(new_final);
            nfa->final_state->add_e_closure(nfa->start_state);
            nfa->start_state = new_start;
            nfa->final_state = new_final;
            return nfa; // returning the modified NFA instead of a new one
        }
        static NFA* positive_closure(NFA* nfa){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            new_start->add_e_closure(nfa->start_state);
            nfa->final_state->add_e_closure(new_final);
            nfa->final_state->add_e_closure(nfa->start_state);
            nfa->start_state = new_start;
            nfa->final_state = new_final;
            return nfa; // returning the modified NFA instead of a new one
        }

};

#endif // NFA_H