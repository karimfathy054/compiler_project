#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "DFA.cpp"
#include "DFADecoder.cpp"
#include "DFAMinimizerMNtheorem.cpp"
#include "DFAMinimizerPartitioning.cpp"

// Test the lexical analyzer using the rules in the file "test.txt"
// this example from Lecture 4 (Dr pdfs) 
int main(int, char**){
    string input_file_path = "../input.txt";
    string rules_file_path = "../lexical rules.txt";
    string dfa_file_path = "../dfa.txt";
    string output_file_path = "../output.txt";
    string symbol_table_file_path = "../symbol_table.txt";

    unordered_map<string, string> symbol_table;
    string input;
    ifstream input_file(input_file_path);
    
    // check for file existance
    if (!input_file)
    {
        cerr << "File not found" << endl;
        exit(1);
    }
    
    cout << "Reading Rules...\n";
    RulesReader r(rules_file_path);
    vector<pair<string, string>> rules = r.get_all_rules();

    cout << "Generating NFA...\n";
    NFAGenerator nfa_gen;
    NFA* nfa = nfa_gen.generateNFA(rules);

    cout << "Generating DFA...\n";
    DFAGenerator dfa_gen;
    DFAState* dfa_state = dfa_gen.generateDFA(nfa, rules, r.get_possible_inputs());
    DFAState::print_dfa(dfa_file_path, dfa_state);
    cout << "Minimizing DFA...\n";

    // DFAMinimizerMNtheorem dfa_minimizer(dfa_state);
    // dfa_minimizer.minimize();

    DFAMinimizerPartitioning dfa_minimizer2(dfa_state);
    dfa_state = dfa_minimizer2.minimize();

    dfa_state->check_all_is_dead();

    // print the dfa states in dfa.txt
    // DFAState::print_dfa(dfa_file_path, dfa_state);
    DFAState::print_dfa(dfa_file_path, dfa_state);

    cout << "Decoding...\n";

    ofstream output_file(output_file_path);

    if(!output_file.is_open()) {
        cerr << "Unable to open file: " << output_file_path << endl;
        return 0;
    }

    int line_number = 0;
    while(getline(input_file, input)) {
        line_number++;

        // remove the line if it's a comment
        size_t pos = input.find("//");
        if(pos != string::npos) input = input.substr(0, pos);

        // remove this for now in case some state accepts \L
        // if(input.empty()) {
        //     continue;
        // }

        DFADecoder dfa_decoder(dfa_state, input, line_number);

        pair<string, string> token;
        try {
            while((token = dfa_decoder.next_token()).first != "") {
                if(token.first == "whitespace") continue;
                
                if(token.first[0] == 'p'){
                    output_file << token.second;
                }
                else{
                    symbol_table[token.second] = token.first;
                    output_file << token.first;
                }
                output_file << "\n";
            }
        } catch(const std::invalid_argument& e) {
            output_file << e.what();
            output_file << "\nEnter Panic Mode...\nSkipping line\n";
            continue;
        }
    }
    if(line_number == 0) {
        // handle empty string incase of empty file
        output_file << DFADecoder(dfa_state, "", line_number).next_token().first;
    }
    output_file.close();

    cout << "Writing Symbol Table...\n";

    ofstream symbol_table_file(symbol_table_file_path);
    if(!symbol_table_file.is_open()) {
        cerr << "Unable to open file: " << symbol_table_file_path << endl;
        return 0;
    }

    for(auto& [token, value]: symbol_table) {
        symbol_table_file << value << " " << token << "\n";
    }

    symbol_table_file.close();
    cout << "Done.";
}