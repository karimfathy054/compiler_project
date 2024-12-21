#include "input_parser.h"
#include <iostream>

string next_token_wrapper(lexical_analyzer &lex)
{
    string token;
    do
    {
        token = lex.next_token();
    } while (token == "whitespace");
    return token;
}

void parse_input(string input_file_path, lexical_analyzer &lex, unordered_map<Symbol *, unordered_map<string, TableEntry>> predictive_parsing_table, Symbol *starting_symbol)
{
    Symbol *program_end = new Symbol("$$");
    program_end->setIsTerminal(true);
    stack<Symbol *> st;
    st.push(program_end);
    st.push(starting_symbol);
    string token = next_token_wrapper(lex);
    while (!st.empty())
    {
        Symbol *top = st.top();
        if (top->getIsTerminal())
        {
            if (top->getName() == token)
            {
                cout << "Matched: " << top->getName() << endl;
                st.pop();
                token = next_token_wrapper(lex);
            }
            else
            {
                cout << "Error: token " << top->getName() << " is added to input" << endl;
                break;
            }
        }
        else
        {
            TableEntry entry = predictive_parsing_table[top][token];
            // check if entry is null or not
            if (entry.getProduction() == nullptr && !entry.getIsSync())
            {
                cerr << "Error: token mismatch ( skipping token " << token << " )" << endl;
                token = next_token_wrapper(lex);
            }
            else if (entry.getIsSync())
            {
                cout << "Error: awaiting follow" << endl;
                st.pop();
            }
            else
            {
                st.pop();
                vector<Symbol *> rhs = entry.getProduction()->getRhs();
                cout << entry.getProduction()->getLhs()->getName() << " -> ";

                for (int i = rhs.size() - 1; i >= 0; i--)
                {
                    st.push(rhs[i]);
                }
                for (Symbol *s : rhs)
                {
                    cout << s->getName() << " ";
                }
                cout << endl;
            }
        }
    }
}