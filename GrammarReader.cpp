#include "GrammarReader.h"
#include <fstream>
#include <regex>
#include <iostream>

vector<string> rules;


GrammarReader::GrammarReader(string grammerFilePath){
    ifstream file(grammerFilePath);
    if(file.fail()){
        cerr << "Error: File not found" << endl;
        return;
    }
    regex rule_start(R"((.*)# (.*))");
    regex rule_structure(R"((.*) ::= (.*))");
    string line;
    while(getline(file, line)){
        smatch match;
        if(regex_match(line, match, rule_start)){
            string old = match[1];
            string new_ = match[2];
            string& s = rules.back();
            s += " "+old;
            rules.push_back(new_);
        }
    }
    file.close();
    //loop over rules and detect lhs and rhs of each rule
    for(string rule: rules){
        smatch match;
        if(regex_match(rule, match, rule_structure)){
            string lhs = match[1];
            string rhs = match[2];
            rhs = regex_replace(rhs, regex(R"(\s+)"), " ");
            lhs = regex_replace(rhs, regex(R"(\s+)"), " ");
            //remove leading and trailing spaces
            lhs = regex_replace(lhs, regex(R"(^\s+|\s+$)"), "");
            rhs = regex_replace(rhs, regex(R"(^\s+|\s+$)"), "");
            
            // TODO: complete the spliting of RHS string and generate a production
            //! Handle Symbol pointers correctly
            
            cout << lhs << " ::= " << rhs << endl;
        }
    }
}