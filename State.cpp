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
    public:
        State(int id){
            state_id = id;
        }
        vector<State*> get_transitions(char symbol){
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
};