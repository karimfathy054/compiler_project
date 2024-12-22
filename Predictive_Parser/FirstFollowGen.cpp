#include "include/FirstFollowGen.h"
#include "include/GrammarReader.h"

using namespace std;

FirstFollowGen::FirstFollowGen(vector<Production*> productions) {
    FirstFollowGen::productions = productions;
    FirstFollowGen::computeFirst();
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
            for(Symbol* innerSymbol: first[symbol]){
                if(innerSymbol->isEpsilon()) {
                    epsilon = innerSymbol;
                    epsilonFound = true;
                }
                else{
                    firstOfRhs.insert(innerSymbol);
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

void FirstFollowGen::computeFirst() {
    bool isChanged = false;
    bool isFirstTime = true;
    while(isChanged || isFirstTime) {
        isChanged = false;
        isFirstTime = false;
        for(Production* production: productions) {
            Symbol* lhs = production->getLhs();
            vector<Symbol*> rhs = production->getRhs();
            unordered_set<Symbol*> firstOfRhs = computeFirstOfRhs(rhs);
            for(Symbol* symbol: firstOfRhs) {
                if(first[lhs].find(symbol) == first[lhs].end()) {
                    first[lhs].insert(symbol);
                    isChanged = true;
                }
            }
        }
    }
}

void FirstFollowGen::displayFirst() {
    cout << "============================================\n";
    cout << "First Set:" << endl;
    for(auto it = first.begin(); it != first.end(); it++) {
        cout << "First(" << it->first->getName() << ") = ";
        for(Symbol* symbol: it->second) {
            if(symbol->isEpsilon()) {
                cout << "epsilon ";
                continue;
            }
            cout << symbol->getName() << " ";
        }
        cout << endl;
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
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}