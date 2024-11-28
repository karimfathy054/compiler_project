#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class State{
    private:
        int state_id;
        unordered_map<char, vector<State*>> transitions;
        vector<State*> e_closure;
        string name;
        /*
            Accepting state definition, is empty if not an accepting state, else contains the name of the token
        */
        string acc_state_def; 
    public:
        State(int id){
            state_id = id;
            acc_state_def = "";
        }
        unordered_map<char, vector<State*>> get_transitions(){
            return transitions;
        }
        vector<State*> get_input_transitions(char symbol){
            if (transitions.find(symbol) == transitions.end()) {
                throw std::runtime_error("No more transitions exist");
            }
            return transitions[symbol];
        }
        void add_transition(char symbol, State* state){
            transitions[symbol].push_back(state);
        }
        void add_e_closure(State* state){
            e_closure.push_back(state);
        }
        vector<State*> get_e_closure(){
            return e_closure;
        }
        void set_acc_state_def(string token_name){
            acc_state_def = token_name;
        }
        string get_acc_state_def(){
            return acc_state_def;
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