#ifndef NFAGENERATOR_H
#define NFAGENERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_set>
#include "NFA.h"

inline int NFA::state_id_counter = 0;
class NFAGenerator{
    
public:
    std::vector<State*> final_accepting_states; //for tracking accepting states in the final NFA
    NFAGenerator(){}
    NFA* generateNFA(std::vector<std::pair<std::string, std::string>> rules);
    void print_nfa(NFA* nfa);
private:
    bool isOperator(char c);
};

#endif