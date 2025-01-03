#include "include/FirstFollowGen.h"
#include "include/GrammarReader.h"

using namespace std;

FirstFollowGen::FirstFollowGen(vector<Production*> productions, Symbol* startSymbol) {
    FirstFollowGen::productions = productions;
    FirstFollowGen::startSymbol = startSymbol;
    FirstFollowGen::first = vector<unordered_set<Symbol*>>(productions.size());
    FirstFollowGen::computeFirstSet();
    FirstFollowGen::computeFollowSet();
}

unordered_set<Symbol*> FirstFollowGen::computeFirstOfRhs(vector<Symbol*> rhs) {
    unordered_set<Symbol*> firstOfRhs;
    bool allHaveEpsilon = true;
    Symbol* epsilon;
    for(Symbol* symbol: rhs) {
        if(symbol->getIsTerminal()) {
            firstOfRhs.insert(symbol);
            return firstOfRhs;
        }
        else {
            bool epsilonFound = false;
            for(int i=0; i<productions.size(); i++) {
                if(productions[i]->getLhs() == symbol) {
                    for(Symbol* innerSymbol: first[i]){
                        if(innerSymbol->isEpsilon()) {
                            epsilon = innerSymbol;
                            epsilonFound = true;
                        }
                        else{
                            firstOfRhs.insert(innerSymbol);
                        }
                    }
                }
            }
            if(!epsilonFound) {
                allHaveEpsilon = false;
                break;
            }
        }
    }
    if(allHaveEpsilon) {
        firstOfRhs.insert(epsilon);
    }
    return firstOfRhs;
}

void FirstFollowGen::computeFirstSet() {
    bool isChanged = true;
    while(isChanged) {
        isChanged = false;
        for(int i=0; i<productions.size(); i++) {
            Symbol* lhs = productions[i]->getLhs();
            vector<Symbol*> rhs = productions[i]->getRhs();
            unordered_set<Symbol*> firstOfRhs = computeFirstOfRhs(rhs);
            for(Symbol* symbol: firstOfRhs) {
                if(first[i].find(symbol) == first[i].end()) {
                    first[i].insert(symbol);
                    isChanged = true;
                }
            }
        }
    }
}

// helper function to slice a vector
vector<Symbol*> slicing(vector<Symbol*>& arr, size_t start)
{
    if(start >= arr.size()) {
        return vector<Symbol*>();
    }
    return vector<Symbol*>(arr.begin() + start, arr.end());
    
}

unordered_set<Symbol*> FirstFollowGen::getFirstSetForSymbol(Symbol* symbol) {
    unordered_set<Symbol*> firstSet;
    for(int i=0; i<productions.size(); i++) {
        if(productions[i]->getLhs() == symbol) {
            for(Symbol* innerSymbol: first[i]) {
                firstSet.insert(innerSymbol);
            }
        }
    }
    return firstSet;
}

unordered_set<Symbol*> FirstFollowGen::getFollowSetForSymbol(Symbol* symbol) {
    return follow[symbol];
}

void FirstFollowGen::computeFollowSet(){
    follow[startSymbol].insert(new Symbol("$"));
    bool isChanged = true;
    while(isChanged){
        isChanged = false;
        for(Production* production: productions) {
            vector<Symbol*> rhs = production->getRhs();
            for(int i=0; i<rhs.size(); i++){
                if(rhs[i]->getIsTerminal()){
                    continue;
                }
                unordered_set<Symbol*> firstSet;
                if(i < rhs.size()-1) {
                    firstSet = computeFirstOfRhs(slicing(rhs, i+1));
                }
                bool nextHasEpsilon = false;
                for(Symbol* symbol: firstSet){
                    if(symbol->isEpsilon()){
                        nextHasEpsilon = true;
                    }
                    else if(follow[rhs[i]].find(symbol) == follow[rhs[i]].end()){
                        follow[rhs[i]].insert(symbol);
                        isChanged = true;
                    }
                }
                if(i == rhs.size()-1 || nextHasEpsilon){
                    for(Symbol* symbol: follow[production->getLhs()]){
                        if(follow[rhs[i]].find(symbol) == follow[rhs[i]].end()){
                            follow[rhs[i]].insert(symbol);
                            isChanged = true;
                        }
                    }
                }
            }
        }
    }
}

void FirstFollowGen::displayFirst() {
    cout << "============================================\n";
    cout << "First Set:" << endl;
    for(int i=0; i<productions.size(); i++) {
        cout << "First(" << productions[i]->getLhs()->getName() << ") = {";
        bool isFirst = true;
        for(Symbol* symbol: first[i]) {
            if(isFirst) {
                isFirst = false;
            }
            else{
                cout << ",";
            }
            if(symbol->isEpsilon()) {
                cout << " 'epsilon'";
                continue;
            }
            cout << " '" << symbol->getName() << "'";
        }
        cout << " }" <<endl;
    }
}

void FirstFollowGen::displayFollow() {
    cout << "============================================\n";
    cout << "Follow Set:" << endl;
    for(auto it = follow.begin(); it != follow.end(); it++) {
        cout << "Follow(" << it->first->getName() << ") = {";
        bool isFirst = true;
        for(Symbol* symbol: it->second) {
            if(isFirst) {
                isFirst = false;
            }
            else{
                cout << ",";
            }
            if(symbol->isEpsilon()) {
                cout << " 'epsilon'";
                continue;
            }
            cout << " '" << symbol->getName() << "'";
        }
        cout << " }" <<endl;
    }
}

vector<std::unordered_set<Symbol*>> FirstFollowGen::getFirst() {
    return first;
}

unordered_map<Symbol*, std::unordered_set<Symbol*>> FirstFollowGen::getFollow() {
    return follow;
}

// int main() {
//     try {
//         std::string filePath = "..//../ll_grammar.txt"; // Replace with the path to your grammar file
//         GrammarReader parser(filePath);
//         parser.displayProductions();
//         vector<Production*> productions = parser.getProductions();
//         FirstFollowGen firstFollowGen(productions, parser.getStartSymbol());
//         firstFollowGen.displayFirst();
//         firstFollowGen.displayFollow();
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
//     return 0;
// }