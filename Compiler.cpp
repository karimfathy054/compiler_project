#include "Compiler.h"
#include <iostream>
#include "include/FirstFollowGen.h"

using namespace std;

// some helper functions
string get_string_from_stack(stack<Symbol *> st)
{
    string str = "";
    while (!st.empty())
    {
        str = st.top()->getName() + str;
        st.pop();
    }
    return str;
}

string get_string_from_vector(vector<Symbol *> vec)
{
    string str = "";
    for (auto &s : vec)
    {
        str += s->getName();
    }
    return str;
}

Compiler::Compiler(
    std::string rules_file_path,
    std::string grammar_file_path,
    std::string input_file_path,
    std::string output_file_name
) {
    this->outputFileName = output_file_name;
    this->rules_file_path = rules_file_path;
    this->grammar_file_path = grammar_file_path;
    this->input_file_path = input_file_path;

    read_grammar();
    compute_first_follow_sets();
    compute_parsing_table();
    prepare_lexical_analyzer();
}

void Compiler::read_grammar() {
    grammar_reader = GrammarReader(grammar_file_path);
    productions = grammar_reader.getProductions();
    grammar_reader.displayProductions();

    LL_Grammar ll_grammar(productions);
    productions = ll_grammar.getProductions();
    ll_grammar.displayProductions();

    symbols = ll_grammar.getSymbols();
    starting_symbol = grammar_reader.getStartSymbol();
    
    non_terminal_symbols = ll_grammar.getNonTerminalSymbols();
}


void Compiler::compute_first_follow_sets() {
    FirstFollowGen firstFollowGen(productions, starting_symbol);
    first = firstFollowGen.getFirst();
    follow = firstFollowGen.getFollow();
    firstFollowGen.displayFirst();
    firstFollowGen.displayFollow();
}

void Compiler::compute_parsing_table() {
    table_generator = ParsingTableGenerator(productions, non_terminal_symbols, first, follow);
    table = table_generator.getTable();
}

void Compiler::prepare_lexical_analyzer() {
    lexical_analyzer = Lexical_analyzer(rules_file_path, input_file_path);
}

string Compiler::next_token_wrapper()
{
    string token;
    do
    {
        token = lexical_analyzer.next_token();
    } while (token == "whitespace");
    return token;
}

void Compiler::parse_input() {
    Symbol *program_end = new Symbol(END_OF_INPUT);
    program_end->setIsTerminal(true);
    vector<string> table_row(3);
    stack<Symbol *> st;
    st.push(program_end);
    st.push(starting_symbol);
    
    string token = next_token_wrapper();

    while (!st.empty())
    {   table_row[0] = get_string_from_stack(st);
        table_row[1] = token;
        Symbol *top = st.top();
        if (top->getIsTerminal())
        {
            if (top->getName() == token)
            {
                table_row[2] = "Matched: "+top->getName();
                st.pop();
                token = next_token_wrapper();
            }
            else
            {
                table_row[2] = "Error: token " + top->getName() + " is added to input";
            }
        }
        else
        {
            TableEntry* entry = table[top][token];
            // check if entry is null or not
            if (entry->getProduction() == nullptr && !entry->getIsSync())
            {
                table_row[2] =  "Error: token mismatch ( skipping token " + token + " )";
                token = next_token_wrapper();
            }
            else if (entry->getIsSync())
            {
                table_row[2] = "Error: awaiting follow";
                st.pop();
            }
            else
            {
                st.pop();
                vector<Symbol *> rhs = entry->getProduction()->getRhs();
                table_row[2] = entry->getProduction()->getLhs()->getName() + " -> " + get_string_from_vector(rhs);

                if(rhs[0]->getName() == "\\L") continue;

                for (int i = rhs.size() - 1; i >= 0; i--)
                {
                    st.push(rhs[i]);
                }
            }
        }
        tableOutput.addRow(table_row);
        // cout << table_row[0] << " " << table_row[1] << " " << table_row[2] << endl;
    }
    tableOutput.saveToMarkdown(outputFileName);
}

void Compiler::remaining_input() {
    string token = lexical_analyzer.next_token();
    if(token == END_OF_INPUT) {
        return;
    }
    cout << "*************************" << endl;
    cout << "Remaining unmatched input" << endl;
    do {
        cout << token << endl;
        token = lexical_analyzer.next_token();
    } while(token != END_OF_INPUT);
}

void Compiler::display_productions() {
    for(auto &p : productions){
        p->displayProduction();
        cout << endl;
    }
}

void Compiler::display_symbols() {
    for(auto &[name, symbol]: symbols) {
        cout << symbol->getName() << (symbol->getIsTerminal()? "(T)": "(NT)") << endl;
    }
}

void Compiler::display_table() {
    table_generator.displayTable();
}


