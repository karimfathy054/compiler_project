#include "include/GrammerReader.h"

using namespace std;

GrammarReader::GrammarReader(string filepath) {
    i = 0;
    cur_line = "";
    file = ifstream(filepath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    readGrammer();
}
 vector<Production*> GrammarReader::getProductions() {
    return productions;
}
void GrammarReader::displayProductions() {
    for(auto production : productions) {
        cout << production->getLhs() << " -> ";
        for(auto rhs : production->getRhs()) {
            cout << rhs << " ";
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
        production = new Production(token, {});

        token = next_token();
        if(token != "=") {
            throw runtime_error("Expected =");
        }

        while((token = next_token()) != "") {
            if(token == "#") break;
            if(token == "|") {
                productions.push_back(production);
                production = new Production(production->getLhs(), {});
                continue;
            }
            production->addRhs(token);
        }
        if(production->getRhs().size() > 0) {
            productions.push_back(production);
        }
    }
}

bool GrammarReader::is_special(char ch) {
    return ch == '|' || ch == '#' || ch == '=' || ch == LETF_TERM || ch == RIGHT_TERM;
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
    if(word[0] == LETF_TERM) {
        string next = get_word();
        string right_terminal_sympol = get_word();
        if(right_terminal_sympol == "" or right_terminal_sympol[0] != RIGHT_TERM) {
            throw runtime_error("Expected " + string(1, RIGHT_TERM));
        }
        return next;
    }
    return word;

}
void GrammarReader::remove_spaces() {
    while(i < cur_line.size() && cur_line[i] == ' ') {
        i++;
    }
}
string GrammarReader::get_word() {
    remove_spaces();
    if(is_special(cur_line[i])) {
        string word = string(1, cur_line[i++]);
        remove_spaces();
        return word;
    }
    string word = "";
    while(i < cur_line.size() && !is_special(cur_line[i]) && cur_line[i] != ' ') {
        word += cur_line[i];
        i++;
    }
    remove_spaces();
    return word;
}

int main() {
    try {
        std::string filePath = "../../ll_grammar.txt"; // Replace with the path to your grammar file
        GrammarReader parser(filePath);
        parser.displayProductions();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
