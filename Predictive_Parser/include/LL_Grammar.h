#pragma once
#include "Production.h"
#include "Symbol.h"
#include "../../Lexical_analyzer/include/lexica.h"
#include <vector>

using namespace std;

class Prod
{
private:
    vector<Symbol *> prod_out;

public:
    Prod(vector<Symbol *> rhs);
    vector<Symbol *> getProd_out();
    void setProd_out(vector<Symbol *> rhs);
};

class LL_Grammar
{
private:
    std::unordered_map<std::string, Symbol*> symbols;
    std::unordered_set<Symbol*> non_terminal_symbols;
    vector<Production*> productions;
    void convert_to_LL_grammmar();
    void replace_Symbol(Symbol *x, vector<Prod *> &productions_with_x, vector<Prod *> &productions_of_x);
    pair<Symbol *, vector<Prod *>> eliminate_left_recursion(Symbol *lhs, vector<Prod *> &prods);
public:
    LL_Grammar(vector<Production *> productions);
    void displayProductions();
    vector<Production *> getProductions() { return productions; }
    std::unordered_map<std::string, Symbol*> getSymbols() { return symbols; }
    std::unordered_set<Symbol*> getNonTerminalSymbols() { return non_terminal_symbols; }
};
