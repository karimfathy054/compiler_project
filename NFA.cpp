#include "State.cpp"
class NFA{
    //TODO: initialize the state_id_counter in main
    static int state_id_counter; 
    private:
        State* start_state;
        State* final_state;
    public:
        
        NFA(char c){
            start_state = new State(state_id_counter++);
            final_state = new State(state_id_counter++);
            start_state->add_transition(c, final_state);
        }
        NFA(State* start_state, State* final_state){
            this->start_state = start_state;
            this->final_state = final_state;
        }

        void mark_accepting(string token_name){
            final_state->set_acc_state_def(token_name);
        }

        State* get_start_state() {
            return start_state;
        }

        static void reset_state_id_counter(){
            state_id_counter = 0;
        }
        static NFA* concatenate(NFA* nfa1, NFA* nfa2){
            nfa1->final_state->add_e_closure(nfa2->start_state);
            return new NFA(nfa1->start_state, nfa2->final_state);;
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
        static NFA* union_(vector<NFA*> nfas){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            for(auto &nfa : nfas){
                new_start->add_e_closure(nfa->start_state);
                nfa->final_state->add_e_closure(new_final);
            }
            return new NFA(new_start, new_final);
        }
        static NFA* kleene_closure(NFA* nfa){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            new_start->add_e_closure(new_final);
            new_start->add_e_closure(nfa->start_state);
            nfa->final_state->add_e_closure(new_final);
            nfa->final_state->add_e_closure(nfa->start_state);
            return new NFA(new_start, new_final);
        }
        static NFA* positive_closure(NFA* nfa){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            new_start->add_e_closure(nfa->start_state);
            nfa->final_state->add_e_closure(new_final);
            nfa->final_state->add_e_closure(nfa->start_state);
            return new NFA(new_start, new_final);
        }

};
int NFA::state_id_counter = 0;
