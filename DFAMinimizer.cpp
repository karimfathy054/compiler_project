#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "State.cpp"
using namespace std;
class DFAMinimizer {
    private:
        unordered_map<int,State*> id_state_map;
        unordered_map<State*,int> state_id_map;
        unordered_set<State*> final_states;
        
    public:
        DFAMinimizer(State* start_state) {
            queue<State*> q;
            unordered_set<State*> visited;
            q.push(start_state);
            while(!q.empty()){
                State* current_state = q.front();
                q.pop();
                visited.insert(current_state);
                id_state_map[current_state->get_state_id()] = current_state; //assuimg unique IDs
                state_id_map[current_state] = current_state->get_state_id();
                if(current_state->get_acc_state_def() != ""){
                    final_states.insert(current_state);
                }
                for(auto& transition:current_state->get_transitions()){
                    for(State* next_state:transition.second){
                        if(visited.find(next_state) == visited.end()){
                            q.push(next_state);
                        }
                    }
                }
            }
        }
        void minimize(){
            // construct the n^2 table
            bool table[id_state_map.size()][id_state_map.size()] = {false};
            // mark all final states with other non final states
            for(int i=0;i<id_state_map.size();i++){
                for(int j=0;j<i;j++){
                    if((final_states.find(id_state_map[i]) != final_states.end() && final_states.find(id_state_map[j]) == final_states.end()) || (final_states.find(id_state_map[i]) == final_states.end() && final_states.find(id_state_map[j]) != final_states.end())){
                        table[i][j] = true;
                    }
                }
            }
            // check each pair with the other according to the input domain
            bool changed = true;
            while(changed){
                changed = false;
                for(int i=0;i<id_state_map.size();i++){
                    for(int j=0;j<i;j++){
                        if(!table[i][j]){
                            set<char> symbols = id_state_map[i]->get_transition_symbols();
                            set<char> symbols2 = id_state_map[j]->get_transition_symbols();
                            set<char> common_domain;
                            set_intersection(symbols.begin(), symbols.end(), symbols2.begin(), symbols2.end(), inserter(common_domain, common_domain.begin())); //has over head but avoids null pointers
                            for(char symbol:common_domain){
                                vector<State*> next_states1 = id_state_map[i]->get_transitions()[symbol];
                                vector<State*> next_states2 = id_state_map[j]->get_transitions()[symbol];
                                int next_state1_id = next_states1[0]->get_state_id(); //assuming state has one transition per symbol
                                int next_state2_id = next_states2[0]->get_state_id();
                                if(table[next_state1_id][next_state2_id] || table[next_state2_id][next_state1_id]){
                                    table[i][j] = true;
                                    changed = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            // TODO:combine unmarked states together
            // TODO: needs more checking
            vector<pair<int,int>> combined_states;
            for(int i=0;i<id_state_map.size();i++){
                for(int j=0;j<i;j++){
                    if(!table[i][j]){
                        combined_states.push_back(make_pair(i,j));
                    }
                }
            }
            unordered_map<State*,State*> new_state_map;
            for(pair<int,int> p:combined_states){
                State* state1 = id_state_map[p.first]; //bigger id
                State* state2 = id_state_map[p.second]; //smaller id 
                if((state1->get_acc_state_def() == "" && state2->get_acc_state_def() == "") || (state1->get_acc_state_def() == state2->get_acc_state_def())){
                    state2->combine_states_outputs(state1);
                    id_state_map[p.first] = state2;
                    new_state_map[state1] = state2;
                }   
            }
            for(auto& state: id_state_map){
                for(auto& transition:state.second->get_transitions()){
                    State* next_state = transition.second[0];
                    if(next_state->get_state_id() != state_id_map[next_state]){
                        state.second->get_transitions()[transition.first][0] = new_state_map[next_state];
                    }
                }
            }

        }

};