#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_set>
#include "NFA.cpp"

using namespace std;

class NFAGenerator{
public:
    NFAGenerator(){}
    NFA* generateNFA(vector<pair<string, string>> rules){
        vector<NFA*> result_nfas;
        for(auto &p : rules){
            string &name = p.first;
            string &def = p.second;
            stack<NFA*> s;
            vector<NFA*> nfas_to_union;
            for(int i = 0; i < def.size(); i++){
                char c = def[i];
                if(isOperator(c)) {
                    if(c == '|') {
                        for(int j = i; j < def.size() and def[j] == '|'; j++) {
                            nfas_to_union.push_back(s.top());
                            s.pop();
                            i = j;
                        }
                        nfas_to_union.push_back(s.top());
                        s.pop();
                        s.push(NFA::union_(nfas_to_union));
                        nfas_to_union.clear();
                    }else if(c == '~') {
                        NFA* first_nfa = s.top();
                        s.pop();
                        NFA* second_nfa = s.top();
                        s.pop();
                        s.push(NFA::concatenate(first_nfa, second_nfa));
                    }else if(c == '*') {
                        NFA* nfa = s.top();
                        s.pop();
                        s.push(NFA::kleene_closure(nfa));
                    }else if(c == '+') {
                        NFA* nfa = s.top();
                        s.pop();
                        s.push(NFA::positive_closure(nfa));
                    }
                }else {
                    if(c == '\\') {
                        i++;
                        c = def[i];
                    }
                    s.push(new NFA(c));
                }
            }
            if(s.size() != 1) throw runtime_error("Invalid Regular Expression!! Should have ended with one NFA, but ended with " + to_string(s.size()));
            s.top()->mark_accepting(name);
            result_nfas.push_back(s.top());
        }
        return NFA::union_(result_nfas);
    }
    void print_nfa(NFA* nfa){
        queue<State*> q;
        unordered_set<int> visited;
        q.push(nfa->get_start_state());
        visited.insert(nfa->get_start_state()->get_state_id());
        while(q.size()) {
            State* state = q.front();
            q.pop();
            cout << "State " << state->get_state_id() << ":\n";
            cout << "Accepting State Definition: " << (state->get_acc_state_def() == ""? "Not Accepting": state->get_acc_state_def()) << endl;
            cout << "Transitions:\n";
            for(auto &p : state->get_transitions()) {
                cout << p.first << " -> ";
                for(auto &s : p.second) {
                    if(!visited.count(s->get_state_id())) {
                        visited.insert(s->get_state_id());
                        q.push(s);
                    }
                    cout << s->get_state_id() << " ";
                }
                cout << endl;
            }
            cout << "E-Closure:\n";
            for(auto &s : state->get_e_closure()) {
                if(!visited.count(s->get_state_id())) {
                    visited.insert(s->get_state_id());
                    q.push(s);
                }
                cout << s->get_state_id() << " ";
            }
            cout << endl;
        }
    }
private:
    bool isOperator(char c){
        return c == '|' || c == '*' || c == '+' || c == '~';
    }
};

int main(){
    vector<pair<string, string>> rules = {
        {"ID", "abc||"},
        {"NUM", "0123456789|||||||||"},
        {"OP", "\\+-\\*/|||*"}
    };
    NFAGenerator nfa_gen;
    NFA* nfa = nfa_gen.generateNFA(rules);
    nfa_gen.print_nfa(nfa);
    return 0;
}