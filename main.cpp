#include "Compiler.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    string rules_file_path = "../../../omar_test_input/rules.txt";
    string grammar_file_path = "../../../omar_test_input/grammar.txt";
    string input_file_path = "../../../omar_test_input/input.txt";
    Compiler compiler(rules_file_path, grammar_file_path, input_file_path);
    cout << "Productions...\n";
    compiler.display_productions();
    cout << "Table...\n";
    compiler.display_table();
    cout << "Result...\n";
    compiler.parse_input();
    
    compiler.remaining_input();
    cout << "Done\n";
    return 0;
}

/*
int main()
{
    string input_file_path = "../../../test_input/input3.txt";
    string rules_file_path = "../../../test_input/lexRules3.txt";
    unordered_map<string, string> symbol_table;
    lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);
    unordered_map<Symbol *, unordered_map<string, TableEntry>> table;

    Symbol *E = new Symbol("E");
    E->setIsTerminal(false);
    Symbol *X = new Symbol("X");
    X->setIsTerminal(false);
    Symbol *T = new Symbol("T");
    T->setIsTerminal(false);
    Symbol *Y = new Symbol("Y");
    Y->setIsTerminal(false);
    Symbol *F = new Symbol("F");
    F->setIsTerminal(false);

    Symbol *plus = new Symbol("add");
    Symbol *star = new Symbol("mul");
    Symbol *lparen = new Symbol("(");
    Symbol *rparen = new Symbol(")");
    Symbol *id = new Symbol("id");

    Production *p1 = new Production(E, {T, X});
    Production *p2 = new Production(X, {plus, T, X});
    Production *p3 = new Production(X, {});
    Production *p4 = new Production(T, {F, Y});
    Production *p5 = new Production(Y, {star, F, Y});
    Production *p6 = new Production(Y, {});
    Production *p7 = new Production(F, {lparen, E, rparen});
    Production *p8 = new Production(F, {id});

    table[E]["id"] = TableEntry(p1);
    table[E]["("] = TableEntry(p1);
    table[E][END_OF_INPUT] = new TableEntry(true);
    table[E][")"] = new TableEntry(true);
    table[X]["add"] = TableEntry(p2);
    table[X][END_OF_INPUT] = TableEntry(p3);
    table[X][")"] = TableEntry(p3);
    table[T]["id"] = TableEntry(p4);
    table[T]["("] = TableEntry(p4);
    table[T][END_OF_INPUT] = new TableEntry(true);
    table[T][")"] = new TableEntry(true);
    table[T]["add"] = new TableEntry(true);
    table[Y]["mul"] = TableEntry(p5);
    table[Y][END_OF_INPUT] = TableEntry(p6);
    table[Y][")"] = TableEntry(p6);
    table[Y]["add"] = TableEntry(p6);
    table[F]["id"] = TableEntry(p8);
    table[F]["("] = TableEntry(p7);
    table[F][END_OF_INPUT] = new TableEntry(true);
    table[F][")"] = new TableEntry(true);
    table[F]["mul"] = new TableEntry(true);
    table[F]["add"] = new TableEntry(true);

    Symbol *program_end = new Symbol(END_OF_INPUT);
    program_end->setIsTerminal(true);
    stack<Symbol *> st;
    st.push(program_end);
    st.push(E);

    parse_input(input_file_path, lex, table, E);

    cout << "*********************" << endl;
    cout << "Remaining input" << endl;
    while (true)
    {
        string token = lex.next_token();
        if (token == END_OF_INPUT)
        {
            break;
        }
        if (token == "whitespace")
        {
            continue;
        }
        cout << token << endl;
    }

    return 0;
}
*/

/*

void test1(
    unordered_map<string, Symbol*> symbols,
    vector<unordered_set<Symbol*>>& first,
    unordered_map<Symbol*, unordered_set<Symbol*>>& follow
    ) {
    // S -> R T
    first.push_back({
        symbols["s"],
        symbols["\\L"],
        symbols["v"],
        symbols["t"]
    });
    // R = s U R b
    first.push_back({
        symbols["s"]
    });
    // R = \L
    first.push_back({
        symbols["\\L"]
    });
    // U = u U
    first.push_back({
        symbols["u"]
    });
    // U = \L
    first.push_back({
        symbols["\\L"]
    });
    // V = v V
    first.push_back({
        symbols["v"]
    });
    // V = \L
    first.push_back({
        symbols["\\L"]
    });
    // T = V t T
    first.push_back({
        symbols["v"],
        symbols["t"]
    });
    // T = \L
    first.push_back({
        symbols["\\L"]
    });
    cout << "Followtin\n";
    // S
    follow[symbols["S"]] = {
        symbols[END_OF_INPUT]
    };
    // R
    follow[symbols["R"]] = {
        symbols["v"],
        symbols["t"],
        symbols["b"],
        symbols[END_OF_INPUT]
    };
    // U
    follow[symbols["U"]] = {
        symbols["b"],
        symbols["s"],
    };
    // V
    follow[symbols["V"]] = {
        symbols["t"]
    };
    // T
    follow[symbols["T"]] = {
        symbols[END_OF_INPUT]
    };
}


void test2(
    unordered_map<string, Symbol*> symbols,
    vector<unordered_set<Symbol*>>& first,
    unordered_map<Symbol*, unordered_set<Symbol*>>& follow
    ) {
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
    cout << "Followtin\n";
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

int main() {
    GrammarReader parser("../ll_grammar.txt");
    vector<Production*> productions = parser.getProductions();
    cout << "Done productions\n";
    unordered_map<string, Symbol*> symbols = parser.getSymbols();
    symbols[END_OF_INPUT] = new Symbol(END_OF_INPUT);

    parser.displayProductions();

    vector<unordered_set<Symbol*>> first;
    unordered_map<Symbol*, unordered_set<Symbol*>> follow;

    test2(symbols, first, follow);
    
    cout << "Tabling...\n";
    unordered_set<Symbol*> non_terminal_symbols;
    for(auto &[_, symbol]: symbols) {
        if(not symbol->getIsTerminal()) non_terminal_symbols.insert(symbol);
    }

    ParsingTableGenerator tableGenerator(productions, non_terminal_symbols, first, follow);

    cout << "Displaying...\n";
    tableGenerator.displayTable();

    // Symbol *program_end = new Symbol(END_OF_INPUT);
    // program_end->setIsTerminal(true);
    // stack<Symbol *> st;
    // st.push(program_end);
    // st.push(symbols["E"]);

    string input_file_path = "../test_input/input_omar.txt";
    string rules_file_path = "../test_input/lexical_rules_omar.txt";

    unordered_map<string, string> symbol_table;

    cout << "Lexing...\n";
    Lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);

    cout << "Parsing...\n";
    // parse_input(input_file_path, lex, tableGenerator.getTable(), symbols["E"]);

    
    cout << "Done\n";

    return 0;
}
*/

