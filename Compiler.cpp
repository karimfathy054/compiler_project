#include "Compiler.h"
#include <iostream>
#include "include/FirstFollowGen.h"
#include "OutputHandler.h"

using namespace std;

// helper function
std::string get_string_from_vector(std::vector<Symbol *> vec)
{
    std::string str = "";
    for (auto &s : vec)
    {
        str += s->getName() + " ";
    }
    return str;
}

Compiler::Compiler(
    std::string rules_file_path,
    std::string grammar_file_path,
    std::string input_file_path
) {
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

    cout << "After recursion and sub\n";
    display_productions();

    Left_Factoring left_factoring(productions);

    left_factoring.leftFactor();

    productions = left_factoring.getNewProductions();

    cout << "+++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "After left factoring\n";
    display_productions();

    symbols = left_factoring.getSymbols();
    starting_symbol = grammar_reader.getStartSymbol();
    
    non_terminal_symbols = left_factoring.getNonTerminalSymbols();
}


void Compiler::compute_first_follow_sets() {
    FirstFollowGen firstFollowGen(productions, starting_symbol);
    first = firstFollowGen.getFirst();
    follow = firstFollowGen.getFollow();

    // Display first and follow sets to md file
    unordered_set<Symbol*> visited;
    for(Symbol* symbol: non_terminal_symbols) {
        if(visited.find(symbol) == visited.end()) {
            outputHandler.add_row_to_first_follow_table(symbol->getName(), 
                firstFollowGen.getFirstSetForSymbol(symbol),
                firstFollowGen.getFollowSetForSymbol(symbol)
            );
            visited.insert(symbol);
        }
    }
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
    stack<Symbol *> st;
    st.push(program_end);
    st.push(starting_symbol);
    
    string token = next_token_wrapper();

    stack<Symbol *> row_stack;
    string row_token;
    string row_action;

    while (!st.empty())
    {   row_stack = st;
        row_token = token;
        Symbol *top = st.top();
        if (top->getIsTerminal())
        {
            if (top->getName() == token)
            {
                row_action = "Matched: "+top->getName();
                st.pop();
                token = next_token_wrapper();
            }
            else
            {
                row_action = "Error: token \'" + top->getName() + "\' is added to input";
                st.pop();
            }
        }
        else
        {
            TableEntry* entry = table[top][token];
            // check if entry is null or not
            if (entry == nullptr)
            {
                row_action =  "Error: token mismatch ( skipping token " + token + " )";
                token = next_token_wrapper();
            }
            else if (entry->getIsSync())
            {
                row_action = "Error: awaiting follow";
                st.pop();
            }
            else
            {
                st.pop();
                vector<Symbol *> rhs = entry->getProduction()->getRhs();
                row_action = entry->getProduction()->getLhs()->getName() + " -> " + get_string_from_vector(rhs);

                if(rhs[0]->getName() == "\\L") continue;

                for (int i = rhs.size() - 1; i >= 0; i--)
                {
                    st.push(rhs[i]);
                }
            }
        }
        outputHandler.add_row_to_output_table(row_stack, row_token, row_action);
    }
    outputHandler.save_tables();
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


