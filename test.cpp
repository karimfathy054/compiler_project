#include "DFA.cpp"
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Test the lexical analyzer using the rules in the file "test.txt"
// this example from Lecture 4 (Dr pdfs) 
int main(int, char**){
    RulesReader r("test.txt");
    NFAGenerator nfa_gen;
    NFA* nfa = nfa_gen.generateNFA(r.rules);
    DFAGenerator dfa_gen;
    dfa_gen.generateDFA(nfa, r.rules);
    dfa_gen.print_dfa();
}