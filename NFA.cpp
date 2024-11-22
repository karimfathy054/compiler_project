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
        void concatenate(NFA* nfa){
            final_state->add_e_closure(nfa->start_state);
            final_state = nfa->final_state;
        }
        void union_(NFA* nfa){
            State* new_start = new State(state_id_counter++);
            new_start->add_e_closure(start_state);
            new_start->add_e_closure(nfa->start_state);
            State* new_final = new State(state_id_counter++);
            final_state->add_e_closure(new_final);
            nfa->final_state->add_e_closure(new_final);
            start_state = new_start;
            final_state = new_final;
        }
        void kleene_star(){
            State* new_start = new State(state_id_counter++);
            State* new_final = new State(state_id_counter++);
            new_start->add_e_closure(new_final);
            new_start->add_e_closure(start_state);
            final_state->add_e_closure(new_final);
            final_state->add_e_closure(start_state);
            start_state = new_start;
            final_state = new_final;
        }

};
