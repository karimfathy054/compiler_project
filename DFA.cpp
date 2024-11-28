#include <bits/stdc++.h>
#include "DFAState.cpp"
using namespace std;


class DFA{
    private:
        DFAState* start_state;
    public:
        DFA(DFAState* start_state){
            this->start_state = start_state;
        }
        DFAState* get_start_state(){
            return start_state;
        }
        void set_start_state(DFAState* start_state){
            this->start_state = start_state;
        }
        

        DFAState* get_state_by_id(int state_id){
            queue<DFAState*> q;
            q.push(start_state);
            while(!q.empty()){
                DFAState* current_state = q.front();
                q.pop();
                if(current_state->get_state_id() == state_id){
                    return current_state;
                }
                unordered_map<char, DFAState*> transitions = current_state->get_transitions();
                for(auto transition : transitions){
                    q.push(transition.second);
                }
            }
            return NULL;
        }
};