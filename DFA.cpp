// #include "NFA.cpp"
#include "NFAGenerator.cpp"
#include "RulesReader.cpp"
#include <iostream>
#include <unordered_set>
#include <climits>


class DFAGenerator{
    private:
        State* start_state;
        std::string set_to_string(const std::set<State*> s) {
            std::string result = "";
            for (State* elem : s) {
                result += std::to_string(elem->get_state_id())+",";
            }
            return result;
        }
    public:
        DFAGenerator(){}
        State* get_start_state(){
            return start_state;
        }
        void generateDFA(NFA* nfa, vector<pair<string, string>> rules){
            int state_id_counter = 0;
            unordered_map<string, State*> dfa_states;
            start_state = new State(state_id_counter++);
            start_state->add_nfa_state(nfa->get_start_state());
            dfa_states[set_to_string(start_state->get_nfa_states())] = start_state;
            queue<State*> states_queue;
            states_queue.push(start_state);
            while(!states_queue.empty()){
                State* curr_state = states_queue.front();
                states_queue.pop();
                unordered_map<char, set<State*>> transitions;
                for(auto &trans: curr_state->get_transitions()) {
                    const char key = trans.first;
                    const vector<State*> states = trans.second;
                    if(transitions.find(key) == transitions.end()){
                        transitions[key] = set<State*>(states.begin(), states.end());
                    }
                    else{
                        transitions[key].insert(states.begin(), states.end());
                    }
                    // l7d hna tmam
                }
                unordered_map<char, vector<State*>> new_transitions;
                for(auto &trans: transitions){
                    set<State*> new_state_set = trans.second;
                    if(dfa_states.find(set_to_string(new_state_set)) == dfa_states.end()){
                        State* new_state = new State(state_id_counter++);
                        for(State* nfa_state: new_state_set){
                            new_state->add_nfa_state(nfa_state);
                        }
                        
                        new_transitions[trans.first] = vector<State*>{new_state};
                        
                        states_queue.push(new_state);
                        dfa_states[set_to_string(new_state_set)] = new_state;
                    }
                    else{
                        new_transitions[trans.first] = vector<State*>{dfa_states[set_to_string(new_state_set)]};
                    }
                }
                curr_state->set_transitions(new_transitions);
                int acc_state = INT_MAX;
                for(auto nfa_state: curr_state->get_nfa_states()){
                    if(nfa_state->get_acc_state_def() != ""){
                        for(int i=0; i<rules.size(); i++){
                            if(rules[i].first == nfa_state->get_acc_state_def()){
                                acc_state = min(i, acc_state);
                                break;
                            }
                        }
                    }
                }
                if(acc_state != INT_MAX){
                    curr_state->set_acc_state_def(rules[acc_state].first);
                }
            }
        }

        void print_dfa(){
            unordered_set<int> visited;
            queue<State*> q;
            q.push(start_state);
            while(!q.empty()){
                State* curr_state = q.front();
                q.pop();
                if(visited.find(curr_state->get_state_id()) != visited.end()) continue;
                visited.insert(curr_state->get_state_id());
                cout << "State: " << curr_state->get_state_id() << endl;
                cout << "Accepting State Definition: " << (curr_state->get_acc_state_def() == ""? "Not Accepting": curr_state->get_acc_state_def()) << endl;
                cout << "NFA States: ";
                for(State* nfa_state: curr_state->get_nfa_states()){
                    cout << nfa_state->get_state_id() << " ";
                }
                cout << endl;
                for(auto &trans: curr_state->get_transitions()){
                    cout << "Transition: " << trans.first << " ";
                    for(State* state: trans.second){
                        cout << state->get_state_id() << " ";
                        q.push(state);
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
        State* get_dfa_start_state(){
            return start_state;
        }
};


// // Test the lexical analyzer using the rules in the file "test.txt"
// // this example from Lecture 4 (Dr pdfs) 
// int main(int, char**){
//     RulesReader r("test.txt");
//     NFAGenerator nfa_gen;
//     NFA* nfa = nfa_gen.generateNFA(r.rules);
//     DFAGenerator dfa_gen;
//     dfa_gen.generateDFA(nfa, r.rules);
//     dfa_gen.print_dfa();
// }