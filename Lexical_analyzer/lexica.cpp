#include "include/lexica.h"

using namespace std;

void Lexical_analyzer::prepare_dfa(std::string &rules_file_path)
{
    RulesReader r(rules_file_path);
    vector<pair<string, string>> rules = r.get_all_rules();
    NFAGenerator nfa_gen;
    NFA *nfa = nfa_gen.generateNFA(rules);
    DFAGenerator dfa_gen;
    DFAState *gen_dfa_state = dfa_gen.generateDFA(nfa, rules, r.get_possible_inputs());
    DFAMinimizerPartitioning dfa_minimizer2(gen_dfa_state);
    gen_dfa_state = dfa_minimizer2.minimize();
    gen_dfa_state->check_all_is_dead();
    this->dfa_start_state = gen_dfa_state;
}
Lexical_analyzer::Lexical_analyzer(string rules_file_path, string input_file_path)
{
    this->rules_file_path = rules_file_path;
    this->input_file_path = input_file_path;
    this->input_file.open(input_file_path);
    if(!input_file.is_open())
    {
        cerr << "Error: input file not found" << endl;
        exit(1);
    }
    this->symbol_table = new unordered_map<string, string>();
    prepare_dfa(rules_file_path);
}
string Lexical_analyzer::next_token()
{
    if(input_file.eof())
    {
        return END_OF_INPUT;
    }
    string lexeme = "";
    string last_accepeted_token = "";
    int last_accepeted_index = 0;
    DFAState *current_state = this->dfa_start_state;
    bool end_reached = false;
    while (true)
    {
        if (current_state->is_dead())
        {
            break;
        }
        char c = input_file.get();
        lexeme += c;
        if (c == EOF)
        {
            end_reached = true;
            break;
        }
        if (current_state->contains_transition(c))
        {
            current_state = current_state->get_transition(c);
            if (current_state->get_acc_state_def() != "")
            {
                last_accepeted_token = current_state->get_acc_state_def();
                last_accepeted_index = lexeme.size();
            }
        }
        else
        {
            break;
        }
    }
    if (last_accepeted_token != "")
    {
        int byte_diff = lexeme.size() - last_accepeted_index;

        input_file.seekg(-byte_diff, ios::cur);

        lexeme = lexeme.substr(0, last_accepeted_index);
        if (last_accepeted_token != "whitespace")
        {
            if (symbol_table->find(last_accepeted_token) == symbol_table->end())
            {
                symbol_table->insert({lexeme, last_accepeted_token});
            }
        }
        return last_accepeted_token;
    }
    else if (end_reached)
    {
        return END_OF_INPUT;
    }
    else
    {
        input_file.seekg(-lexeme.size() + 1, ios::cur);
        cerr << "Invalid input";
    }
    return "";
}

unordered_map<string, string> Lexical_analyzer::get_symbol_table()
{
    return *symbol_table;
}
