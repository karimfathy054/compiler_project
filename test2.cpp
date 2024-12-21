// #include "lexica.cpp"
#include "include/GrammerReader.h"
#include "include/TableEntry.h"
#include "lexica.cpp"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string input_file_path = "../../../test_input/input2.txt";
    string rules_file_path = "../../../test_input/lexrules.txt";
    unordered_map<string, string> symbol_table;
    lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);
    unordered_map<Symbol*,unordered_map<string, TableEntry>> table;
    Symbol* S = new Symbol("S");
    S->setIsTerminal(false);
    Symbol* R = new Symbol("R");
    R->setIsTerminal(false);
    Symbol* U = new Symbol("U");
    U->setIsTerminal(false);
    Symbol* V = new Symbol("V");
    V->setIsTerminal(false);
    Symbol* T = new Symbol("T");
    T->setIsTerminal(false);

    Symbol* s = new Symbol("s");
    Symbol* v = new Symbol("v");
    Symbol* t = new Symbol("t");
    Symbol* u = new Symbol("u");
    Symbol* b = new Symbol("b");

    Production* p1 = new Production(S,{R,T});
    Production* p2 = new Production(R,{s,U,R,b});
    Production* p3 = new Production(R,{});
    Production* p4 = new Production(U,{u,U});
    Production* p5 = new Production(U,{});
    Production* p6 = new Production(V,{v,V});
    Production* p7 = new Production(V,{});
    Production* p8 = new Production(T,{V,t,T});
    Production* p9 = new Production(T,{});

    table[S]["s"] = TableEntry(p1);
    table[S]["v"] = TableEntry(p1);
    table[S]["t"] = TableEntry(p1);
    table[S]["$$"] = TableEntry(p1);
    table[R]["s"] = TableEntry(p2);
    table[R]["v"] = TableEntry(p3);
    table[R]["t"] = TableEntry(p3);
    table[R]["b"] = TableEntry(p3);
    table[R]["$$"] = TableEntry(p3);
    table[U]["u"] = TableEntry(p4);
    table[U]["s"] = TableEntry(p5);
    table[U]["b"] = TableEntry(p5);
    table[V]["v"] = TableEntry(p6);
    table[V]["t"] = TableEntry(p7);
    table[T]["v"] = TableEntry(p8);
    table[T]["t"] = TableEntry(p8);
    table[T]["$$"] = TableEntry(p9);

    Symbol* program_end = new Symbol("$$");
    program_end->setIsTerminal(true);
    stack<Symbol*> st;
    st.push(program_end);
    st.push(S);
    string token = lex.next_token();
    while(!st.empty()){
        Symbol* top = st.top();
        if(top->getIsTerminal()){
            if(top->getName() == token){
                cout << "Matched: " << top->getName() << endl;
                st.pop();
                token = lex.next_token();
            }
            else{
                cout << "Error: token "<<top->getName()<<" is added to input" << endl;
                break;
            }
        }
        else{
            TableEntry entry = table[top][token];
            if(entry.getIsSync()){
                cout << "Error: awaiting follow" << endl;
                st.pop();
                break;
            }
            else{
                st.pop();
                vector<Symbol*> rhs = entry.getProduction()->getRhs();
                cout << entry.getProduction()->getLhs()->getName() << " -> ";
                
                for(int i = rhs.size()-1; i >=0 ; i--){
                    st.push(rhs[i]);
                    cout << rhs[i]->getName() << " ";
                }
                cout << endl;
            }
        }
        
    }

    while (true)
    {
        string token = lex.next_token();
        if (token == "$$")
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