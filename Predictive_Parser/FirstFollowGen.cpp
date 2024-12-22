#include "include/FirstFollowGen.h"
#include "include/GrammarReader.h"

using namespace std;

FirstFollowGen::FirstFollowGen(vector<Production*> productions) {
    FirstFollowGen::productions = productions;
    FirstFollowGen::first = vector<unordered_set<Symbol*>>(productions.size());
    FirstFollowGen::computeFirstSet();
    FirstFollowGen::computeFollowSet();
}

unordered_set<Symbol*> FirstFollowGen::computeFirstOfRhs(vector<Symbol*> rhs, int productionIndex) {
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
    bool isChanged = false;
    bool isFirstTime = true;
    while(isChanged || isFirstTime) {
        isChanged = false;
        isFirstTime = false;
        for(int i=0; i<productions.size(); i++) {
            Symbol* lhs = productions[i]->getLhs();
            vector<Symbol*> rhs = productions[i]->getRhs();
            unordered_set<Symbol*> firstOfRhs = computeFirstOfRhs(rhs, i);
            for(Symbol* symbol: firstOfRhs) {
                if(first[i].find(symbol) == first[i].end()) {
                    first[i].insert(symbol);
                    isChanged = true;
                }
            }
        }
    }
}

void FirstFollowGen::computeFollowSet(){

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

int main() {
    try {
        std::string filePath = "..//../ll_grammar.txt"; // Replace with the path to your grammar file
        GrammarReader parser(filePath);
        parser.displayProductions();
        vector<Production*> productions = parser.getProductions();
        FirstFollowGen firstFollowGen(productions);
        firstFollowGen.displayFirst();
        firstFollowGen.displayFollow();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}