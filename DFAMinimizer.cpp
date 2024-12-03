#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "DFAState.cpp"
using namespace std;
class DFAMinimizer {
    private:
        unordered_map<int,DFAState*> id_state_map;
        unordered_map<DFAState*,int> state_id_map;
        unordered_set<DFAState*> final_states;
        
    public:
        DFAMinimizer(DFAState* start_state) {
            queue<DFAState*> q;
            unordered_set<DFAState*> visited;
            q.push(start_state);
            while(!q.empty()){
                DFAState* current_state = q.front();
                q.pop();
                visited.insert(current_state);

                id_state_map[current_state->get_state_id()] = current_state; //assuimg unique IDs
                state_id_map[current_state] = current_state->get_state_id();

                if(current_state->get_acc_state_def() != ""){
                    final_states.insert(current_state);
                }

                for(auto& [input, next_state]: current_state->get_transitions()){
                    if(visited.find(next_state) == visited.end()){
                        q.push(next_state);
                    }
                }
            }
        }
        bool mark_cell(DFAState* first_state , DFAState* second_state){
            if(final_states.find(first_state) != final_states.end() && final_states.find(second_state) == final_states.end()){
                return true;
            }
            if(final_states.find(first_state) == final_states.end() && final_states.find(second_state) != final_states.end()){
                return true;
            }
            if(final_states.find(first_state) != final_states.end() && final_states.find(second_state) != final_states.end() && first_state->get_acc_state_def() == second_state->get_acc_state_def()){
                return false;
            }
            return false;
        }

        void minimize(){
            // construct the n^2 table
            bool table[id_state_map.size()][id_state_map.size()];
            for (int i=0;i<id_state_map.size();i++){
                for(int j=0;j<id_state_map.size();j++){
                    table[i][j] = false;
                }
            }
            // mark all final states with other non final states
            for(int i=0;i<id_state_map.size();i++){
                for(int j=0;j<i;j++){
                    if(mark_cell(id_state_map[i],id_state_map[j])){
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
                            // Since it's a DFA, all states have the same input domain
                            // set<char> symbols = id_state_map[i]->get_transition_symbols();
                            // set<char> symbols2 = id_state_map[j]->get_transition_symbols();
                            // set<char> common_domain;
                            // set_intersection(symbols.begin(), symbols.end(), symbols2.begin(), symbols2.end(), inserter(common_domain, common_domain.begin())); //has over head but avoids null pointers
                            for(char symbol: id_state_map[i]->get_transition_symbols()){
                                DFAState* next_states1 = id_state_map[i]->get_transition(symbol);
                                DFAState* next_states2 = id_state_map[j]->get_transition(symbol);
                                int next_state1_id = next_states1->get_state_id(); //assuming state has one transition per symbol
                                int next_state2_id = next_states2->get_state_id();
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
            unordered_map<DFAState*,DFAState*> new_state_map;
            for(pair<int,int> p:combined_states){
                DFAState* state1 = id_state_map[p.first]; //bigger id
                DFAState* state2 = id_state_map[p.second]; //smaller id 
                if(state1->get_acc_state_def() == state2->get_acc_state_def()){
                    state2->combine_states_outputs(state1);
                    id_state_map[p.first] = state2;
                    new_state_map[state1] = state2;
                }   
            }
            for(auto& state: id_state_map){
                for(auto& transition: state.second->get_transitions()){
                    DFAState* next_state = transition.second;
                    if(next_state->get_state_id() != state_id_map[next_state]){
                        state.second->get_transitions()[transition.first] = new_state_map[next_state];
                    }
                }
            }

        }

};