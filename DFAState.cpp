#include "unordered_map"
#include "vector"
#include "string"
#include <stdexcept>
using namespace std;

class DFAState {
private:
    int state_id;
    unordered_map<char, DFAState*> transitions;
    string name;
    vector<string> acc_state_defs; 
public:
    DFAState(int state_id){
        this->state_id = state_id;
        acc_state_defs ={};
        name = "";
    }
    DFAState(int state_id, vector<string> acc_state_defs){
        this->state_id = state_id;
        this->acc_state_defs = acc_state_defs;
        name = "";
    }
    string get_top_accetping_state(){
        if(acc_state_defs.size() == 0){
            throw std::runtime_error("No accepting state");
        }
        // TODO : return the state with the highest priority
        return acc_state_defs[0];
    }
    unordered_map<char, DFAState*> get_transitions(){
        return transitions;
    }
    DFAState* get_input_transitions(char symbol){
        if (transitions.find(symbol) == transitions.end()) {
            throw std::runtime_error("No more transitions exist");
        }
        return transitions[symbol];
    }
    void set_transition(char symbol, DFAState* state){
        transitions[symbol] = (state);
    }
    void add_acc_state_def(string token_name){
        acc_state_defs.push_back(token_name);
    }
    vector<string> get_acc_state_defs(){
        return acc_state_defs;
    }
    string get_name(){
        return name;
    }
    void set_name(string name){
        this->name = name;
    }
    int get_state_id(){
        return state_id;
    }
};