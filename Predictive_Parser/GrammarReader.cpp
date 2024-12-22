#include "include/GrammarReader.h"

using namespace std;

GrammarReader::GrammarReader(string filepath) {
    i = 0;
    cur_line = "";
    file = ifstream(filepath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    start_symbol = nullptr;
    readGrammer();
}
 vector<Production*> GrammarReader::getProductions() {
    return productions;
}
void GrammarReader::displayProductions() {
    for(Production* production : productions) {
        cout << production->getLhs()->getName() 
        << (production->getLhs()->getIsTerminal()? "(T)": "(NT)")
        << " -> ";
        for(Symbol* rhs : production->getRhs()) {
            cout << rhs->getName() << (rhs->getIsTerminal()? "(T)": "(NT)") << " ";
        }
        cout << endl;
    }
}

void GrammarReader::readGrammer() {
    string token;
    Production* production;

    token = next_token();
    if(token != "#") {
        throw runtime_error("Expected #");
    }

    while((token = next_token()) != "") {
        Symbol* lhs = getSymbol(token);
        lhs->setIsTerminal(false);
        if(start_symbol == nullptr) {
            start_symbol = lhs;
        }
        production = new Production(lhs, {});
        

        token = next_token();
        if(token != EQUALS) {
            throw runtime_error("Expected " + string(EQUALS));
        }

        while((token = next_token()) != "") {
            if(token == "#") break;
            if(token == "|") {
                productions.push_back(production);
                production = new Production(production->getLhs(), {});
                continue;
            }
            production->addRhs(getSymbol(token));
        }
        if(production->getRhs().size() > 0) {
            productions.push_back(production);
        }
    }

    cleanSymbols();
}

void GrammarReader::cleanSymbols() {
    unordered_map<string, Symbol*> new_symbols;
    for(auto &[name, symbol]: symbols) {
        string new_name = name;
        if(new_name != EPSILON and new_name[0] == '\\') new_name = new_name.substr(1);
        
        symbol->setName(new_name);
        new_symbols[new_name] = symbol;
    }
    symbols = new_symbols;
}

int GrammarReader::is_special(char ch) {
    if (ch == '|' || ch == '#' || ch == '=' || ch == ':') return 0;
    if(ch == LETF_TERM || ch == RIGHT_TERM) return 1;
    return 2;
}
string GrammarReader::next_token() {
    if(i == cur_line.size()) {
        i = 0;
        cur_line = "";
        // keep reading untill we get a non empty line or file ends
        while(cur_line == "") {
            if(not getline(file, cur_line)) {
                return "";
            }
        }
    }
    string word = get_word();
    if(word == "") {
        return "";
    }
    
    // cout << word << endl;
    return word;

}
void GrammarReader::remove_spaces() {
    while(i < cur_line.size() && cur_line[i] == ' ') {
        i++;
    }
}
string GrammarReader::get_word() {
    remove_spaces();
    string word = string(1, cur_line[i++]);

    if(i < cur_line.size() and word[0] == '\\') {
        word += cur_line[i++];
        return word;
    }

    if(word[0] == LETF_TERM) {
        word = "";
        while(i < cur_line.size() && cur_line[i] != RIGHT_TERM) {
            word += cur_line[i++];
        }
        if(i == cur_line.size()) {
            throw runtime_error("Expected " + RIGHT_TERM);
        }
        i++;
        return word;
    }

    while(i < cur_line.size() && is_special(cur_line[i]) == is_special(cur_line[i-1]) && cur_line[i] != ' ') {
        word += cur_line[i++];
    }
    
    remove_spaces();
    return word;
}

Symbol* GrammarReader::getSymbol(string name) {
    if(symbols.find(name) == symbols.end()) {
        symbols[name] = new Symbol(name);
    }
    return symbols[name];
}

std::unordered_map<std::string, Symbol*> GrammarReader::getSymbols() {
    return symbols;
}

Symbol* GrammarReader::getStartSymbol() {
    return start_symbol;
}