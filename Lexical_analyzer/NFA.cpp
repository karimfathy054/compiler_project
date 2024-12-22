#include "include/NFA.h"

using namespace std;

NFA::NFA(){
    start_state = new State(state_id_counter++);
    final_state = new State(state_id_counter++);
    start_state->add_e_closure(final_state);
}
NFA::NFA(char c){
    start_state = new State(state_id_counter++);
    final_state = new State(state_id_counter++);
    start_state->add_transition(c, final_state);
}
NFA::NFA(State* start_state, State* final_state){
    this->start_state = start_state;
    this->final_state = final_state;
}

void NFA::mark_accepting(string token_name){
    final_state->set_acc_state_def(token_name);
}

State* NFA::get_start_state() {
    return start_state;
}
State* NFA::get_final_state() {
    return final_state;
}