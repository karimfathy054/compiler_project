#include "DFAState.cpp"

class DFAMinimizer2 {
private:
    DFAState* start_state;
    vector<DFAState*> all_states;
    
    vector<DFAState*> get_all_states(DFAState* start_state) {
        vector<DFAState*> states;

        queue<DFAState*> q;
        unordered_set<DFAState*> visited;
        q.push(start_state);


        while(!q.empty()){
            DFAState* current_state = q.front();
            q.pop();

            states.push_back(current_state);

            for(auto& [_, next_state]: current_state->get_transitions()){
                if(visited.count(next_state) == 0){
                    visited.insert(next_state);
                    q.push(next_state);
                }
            }
        }
        return states;
    }
    unordered_map<string, vector<DFAState*>> split_on_accepting_states(vector<DFAState*> all_states) {
        unordered_map<string, vector<DFAState*>> acc_states;

        for(DFAState* current_state: all_states)
            acc_states[current_state->get_acc_state_def()].push_back(current_state);
        
        return acc_states;
    }
public:
    DFAMinimizer2(DFAState* start_state) {
        this->start_state = start_state;
        this->all_states = get_all_states(start_state);
    }
    DFAState* minimize() {
        unordered_map<string, vector<DFAState*>> acc_states = split_on_accepting_states(all_states);

        unordered_map<DFAState*, int> state_group_map;
        vector<vector<DFAState*>> groups;
        for(auto& [_, states]: acc_states){
            groups.push_back(states);
            for(DFAState* state: states){
                state_group_map[state] = groups.size()-1;
            }
        }

        bool changed = true;
        while(changed){
            changed = false;
            unordered_map<DFAState*, int> new_state_group_map;
            vector<vector<DFAState*>> new_groups;

            for(vector<DFAState*>& group: groups){
                // always add the first state in a new group
                new_groups.push_back({group[0]});
                new_state_group_map[group[0]] = new_groups.size()-1;
                for(int i = 1; i < group.size(); i++) {
                    DFAState* state1 = group[i];
                    for(int j = 0; j < i; j++) {
                        // check each state with previous states to ensure their groups have been already decided
                        // check if state1[i] is equivalent to state2[j]
                        // if same_group add i to the group of j
                        DFAState* state2 = group[j];
                        bool same_group = true;

                        for(auto& [input, _]: state1->get_transitions()) {
                            DFAState* next_state1 = state1->get_transition(input);
                            DFAState* next_state2 = state2->get_transition(input);

                            if(state_group_map[next_state1] != state_group_map[next_state2]) {
                                same_group = false;
                                break;
                            }
                        }

                        if(same_group) {
                            int state2_group = new_state_group_map[state2];
                            new_groups[state2_group].push_back(state1);
                            new_state_group_map[state1] = state2_group;
                            break;
                        }
                    }
                    // check state[i] have not been added to a group
                    if(new_state_group_map.count(state1) == 0) {
                        new_groups.push_back({state1});
                        new_state_group_map[state1] = new_groups.size()-1;
                    }
                }
            }
            changed = groups != new_groups;

            groups = new_groups;
            state_group_map = new_state_group_map;
        }
        
        int state_id_counter = 0;
        vector<DFAState*> new_states;
        
        for(vector<DFAState*>& group: groups) {
            DFAState* new_state = new DFAState(state_id_counter++);
            new_state->set_acc_state_def(group[0]->get_acc_state_def());

            new_states.push_back(new_state);
        }

        for(int i = 0; i < groups.size(); i++) {
            DFAState* new_state = new_states[i];
            for(auto& [input, next_state]: groups[i][0]->get_transitions()) {
                new_state->set_transition(input, new_states[state_group_map[next_state]]);
            }
        }

        // return the equivalent of the starting state
        return new_states[state_group_map[start_state]];
    }
};