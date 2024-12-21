#include "lexica.h"
#include "RulesReader.cpp"
#include "NFAGenerator.cpp"
#include "DFAMinimizerPartitioning.cpp"

void lexical_analyzer::prepare_dfa(std::string &rules_file_path)
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
lexical_analyzer::lexical_analyzer(string rules_file_path, string input_file_path, unordered_map<string, string> *symbol_table)
{
    this->rules_file_path = rules_file_path;
    this->input_file_path = input_file_path;
    this->symbol_table = symbol_table;
    this->input_file.open(input_file_path);
    prepare_dfa(rules_file_path);
}
string lexical_analyzer::next_token()
{
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
                (*symbol_table)[lexeme] = last_accepeted_token;
            }
        }
        return last_accepeted_token;
    }
    else if (end_reached)
    {
        return "$$";
    }
    else
    {
        input_file.seekg(-lexeme.size() + 1, ios::cur);
        cerr << "Invalid input";
    }
    return "";
}

// int main()
// {
//     string input_file_path = "input.txt";
//     string rules_file_path = "lexical rules.txt";
//     unordered_map<string, string> symbol_table;
//     lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);
//     while (true)
//     {
//         string token = lex.next_token();
//         if (token == "%%")
//         {
//             break;
//         }
//         if (token == "whitespace")
//         {
//             continue;
//         }
//         cout << token << endl;
//     }
//     return 0;
// }