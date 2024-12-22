#ifndef DFA_H
#define DFA_H

#include "NFAGenerator.h"
#include "RulesReader.h"
#include "DFAState.h"
#include "State.h"
#include <iostream>
#include <unordered_set>
#include <climits>

class DFAGenerator{
    private:
        std::string set_to_string(const std::set<State*> s);
    public:
        DFAGenerator(){}
        DFAState* generateDFA(NFA* nfa, std::vector<std::pair<std::string, std::string>> rules, std::unordered_set<char> possible_inputs);
};

#endif