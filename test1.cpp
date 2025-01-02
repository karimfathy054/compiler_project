// // #include "lexica.cpp"
// #include "include/GrammerReader.h"
// #include "include/TableEntry.h"
// #include "lexica.h"
// #include <iostream>
// #include <vector>
// using namespace std;

// string next_token_wrapper(lexical_analyzer &lex)
// {
//     string token;
//     do
//     {
//         token = lex.next_token();
//     } while (token == "whitespace");
//     return token;
// }
// int main()
// {
//     string input_file_path = "../../../test_input/input3.txt";
//     string rules_file_path = "../../../test_input/lexRules3.txt";
//     unordered_map<string, string> symbol_table;
//     lexical_analyzer lex(rules_file_path, input_file_path, &symbol_table);
//     unordered_map<Symbol *, unordered_map<string, TableEntry>> table;

//     Symbol *E = new Symbol("E");
//     E->setIsTerminal(false);
//     Symbol *X = new Symbol("X");
//     X->setIsTerminal(false);
//     Symbol *T = new Symbol("T");
//     T->setIsTerminal(false);
//     Symbol *Y = new Symbol("Y");
//     Y->setIsTerminal(false);
//     Symbol *F = new Symbol("F");
//     F->setIsTerminal(false);

//     Symbol *plus = new Symbol("add");
//     Symbol *star = new Symbol("mul");
//     Symbol *lparen = new Symbol("(");
//     Symbol *rparen = new Symbol(")");
//     Symbol *id = new Symbol("id");

//     Production *p1 = new Production(E, {T, X});
//     Production *p2 = new Production(X, {plus, T, X});
//     Production *p3 = new Production(X, {});
//     Production *p4 = new Production(T, {F, Y});
//     Production *p5 = new Production(Y, {star, F, Y});
//     Production *p6 = new Production(Y, {});
//     Production *p7 = new Production(F, {lparen, E, rparen});
//     Production *p8 = new Production(F, {id});

//     table[E]["id"] = TableEntry(p1);
//     table[E]["("] = TableEntry(p1);
//     table[E][END_OF_INPUT] = new TableEntry(true);
//     table[E][")"] = new TableEntry(true);
//     table[X]["add"] = TableEntry(p2);
//     table[X][END_OF_INPUT] = TableEntry(p3);
//     table[X][")"] = TableEntry(p3);
//     table[T]["id"] = TableEntry(p4);
//     table[T]["("] = TableEntry(p4);
//     table[T][END_OF_INPUT] = new TableEntry(true);
//     table[T][")"] = new TableEntry(true);
//     table[T]["add"] = new TableEntry(true);
//     table[Y]["mul"] = TableEntry(p5);
//     table[Y][END_OF_INPUT] = TableEntry(p6);
//     table[Y][")"] = TableEntry(p6);
//     table[Y]["add"] = TableEntry(p6);
//     table[F]["id"] = TableEntry(p8);
//     table[F]["("] = TableEntry(p7);
//     table[F][END_OF_INPUT] = new TableEntry(true);
//     table[F][")"] = new TableEntry(true);
//     table[F]["mul"] = new TableEntry(true);
//     table[F]["add"] = new TableEntry(true);

//     Symbol *program_end = new Symbol(END_OF_INPUT);
//     program_end->setIsTerminal(true);
//     stack<Symbol *> st;
//     st.push(program_end);
//     st.push(E);

//     string token = next_token_wrapper(lex);

//     while (!st.empty())
//     {
//         Symbol *top = st.top();
//         if (top->getIsTerminal())
//         {
//             if (top->getName() == token)
//             {
//                 cout << "Matched: " << top->getName() << endl;
//                 st.pop();
//                 token = next_token_wrapper(lex);
//             }
//             else
//             {
//                 cout << "Error: token " << top->getName() << " is added to input" << endl;
//                 break;
//             }
//         }
//         else
//         {
//             TableEntry entry = table[top][token];
//             // check if entry is null or not
//             if (entry.getProduction() == nullptr && !entry.getIsSync())
//             {
//                 cerr << "Error: token mismatch ( skipping token " << token << " )" << endl;
//                 token = next_token_wrapper(lex);
//             }
//             else if (entry.getIsSync())
//             {
//                 cout << "Error: awaiting follow" << endl;
//                 st.pop();
//             }
//             else
//             {
//                 st.pop();
//                 vector<Symbol *> rhs = entry.getProduction()->getRhs();
//                 cout << entry.getProduction()->getLhs()->getName() << " -> ";

//                 for (int i = rhs.size() - 1; i >= 0; i--)
//                 {
//                     st.push(rhs[i]);
//                     cout << rhs[i]->getName() << " ";
//                 }
//                 cout << endl;
//             }
//         }
//     }

//     cout << "*********************" << endl;
//     cout << "Remaining input" << endl;
//     while (true)
//     {
//         string token = lex.next_token();
//         if (token == END_OF_INPUT)
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