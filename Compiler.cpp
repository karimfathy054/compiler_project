#include "Compiler.h"
#include <iostream>

using namespace std;

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

    symbols = grammar_reader.getSymbols();
    symbols[END_OF_INPUT] = new Symbol(END_OF_INPUT);

    starting_symbol = grammar_reader.getStartSymbol();
    
    for(auto &[_, symbol]: symbols) {
        if(not symbol->getIsTerminal()) non_terminal_symbols.insert(symbol);
    }
}


// todo
void Compiler::compute_first_follow_sets() {
    // E -> T E'
    first.push_back({
        symbols["id"],
        symbols["("]
    });
    // E' -> + T E'
    first.push_back({
        symbols["+"]
    });
    // E' -> \L
    first.push_back({
        symbols["\\L"]
    });
    // T -> F T'
    first.push_back({
        symbols["id"],
        symbols["("]
    });
    // T' -> * F T'
    first.push_back({
        symbols["*"]
    });
    // T' -> \L
    first.push_back({
        symbols["\\L"]
    });
    // F -> ( E )
    first.push_back({
        symbols["("]
    });
    // F -> id
    first.push_back({
        symbols["id"]
    });
    // E
    follow[symbols["E"]] = {
        symbols[")"],
        symbols[END_OF_INPUT]
    };
    // E'
    follow[symbols["Ed"]] = {
        symbols[")"],
        symbols[END_OF_INPUT]
    };
    // T
    follow[symbols["T"]] = {
        symbols["+"],
        symbols[")"],
        symbols[END_OF_INPUT]
    };
    // T'
    follow[symbols["Td"]] = {
        symbols["+"],
        symbols[")"],
        symbols[END_OF_INPUT]
    };
    // F
    follow[symbols["F"]] = {
        symbols["*"],
        symbols["+"],
        symbols[")"],
        symbols[END_OF_INPUT]
    };
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
    while (!st.empty())
    {
        Symbol *top = st.top();
        if (top->getIsTerminal())
        {
            if (top->getName() == token)
            {
                cout << "Matched: " << top->getName() << endl;
                st.pop();
                token = next_token_wrapper();
            }
            else
            {
                cout << "Error: token " << top->getName() << " is added to input" << endl;
                break;
            }
        }
        else
        {
            TableEntry* entry = table[top][token];
            // check if entry is null or not
            if (entry->getProduction() == nullptr && !entry->getIsSync())
            {
                cerr << "Error: token mismatch ( skipping token " << token << " )" << endl;
                token = next_token_wrapper();
            }
            else if (entry->getIsSync())
            {
                cout << "Error: awaiting follow" << endl;
                st.pop();
            }
            else
            {
                st.pop();
                vector<Symbol *> rhs = entry->getProduction()->getRhs();
                entry->getProduction()->displayProduction();
                cout << endl;

                if(rhs[0]->getName() == "\\L") continue;

                for (int i = rhs.size() - 1; i >= 0; i--)
                {
                    st.push(rhs[i]);
                }
            }
        }
    }
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
    grammar_reader.displayProductions();
}

void Compiler::display_table() {
    table_generator.displayTable();
}

