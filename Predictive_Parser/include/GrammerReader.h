#ifndef GRAMMERREADER_H
#define GRAMMERREADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Production.h"

#define LETF_TERM '\''
#define RIGHT_TERM '\''

class GrammarReader {
public:

    GrammarReader(std::string filepath);
    std::vector<Production*> getProductions();
    void displayProductions();

private:
    int i;
    std::ifstream file;
    std::string cur_line;
    std::vector<Production*> productions;

    void readGrammer();
    bool is_special(char ch);
    std::string next_token();
    void remove_spaces();
    std::string get_word();
};

#endif // GRAMMERREADER_H