#include "include/LL_Grammar.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

Prod::Prod(vector<Symbol *> rhs)
{
    this->prod_out = rhs;
}
vector<Symbol *> Prod::getProd_out()
{
    return this->prod_out;
}
void Prod::setProd_out(vector<Symbol *> rhs)
{
    this->prod_out = rhs;
}


LL_Grammar::LL_Grammar(vector<Production *> productions)
{
    this->productions = productions;
    this->convert_to_LL_grammmar();
}

void LL_Grammar::replace_Symbol(Symbol *x, vector<Prod *> &productions_with_x, vector<Prod *> &productions_of_x) {
    vector<Prod *> new_productions_with_x;

    for(int i = 0; i < productions_with_x.size(); i++) {
        Prod *production_with_x = productions_with_x[i];
        vector<Symbol*> prod_out = production_with_x->getProd_out();
        if(prod_out[0] == x) {
            // B x y -> x y
            prod_out.erase(prod_out.begin());

            for (Prod *p2 : productions_of_x)
            {
                if(p2->getProd_out()[0]->getName() == EPSILON) {
                    new_productions_with_x.push_back(new Prod(prod_out));
                    continue;
                }
                // B = l l -> A = l l x y
                vector<Symbol*> temp(p2->getProd_out());
                temp.insert(temp.end(), prod_out.begin(), prod_out.end());

                new_productions_with_x.push_back(new Prod(temp));
            }
        } else {
            // no subs
            new_productions_with_x.push_back(production_with_x);
        }
    }
    productions_with_x = new_productions_with_x;

}

pair<Symbol*,vector<Prod*>> LL_Grammar::eliminate_left_recursion(Symbol *lhs, vector<Prod *> &prods) {
    vector<Prod *> prods_alpha;
    vector<Prod *> prods_beta;
    for (Prod *p : prods)
    {
        vector<Symbol *> prod = p->getProd_out();
        if(prod.size() == 0)
        {
            continue;
        }
        if (prod[0] == lhs)
        {
            prods_alpha.push_back(p);
        }
        else
        {
            prods_beta.push_back(p);
        }
    }
    if(prods_alpha.size() == 0)
    {
        return make_pair(nullptr,vector<Prod*>());
    }
    Symbol *new_symbol = new Symbol(lhs->getName() + "'");
    new_symbol->setIsTerminal(false);
    for(Prod *p : prods_alpha)
    {
        vector<Symbol *> prod = p->getProd_out();
        prod.erase(prod.begin());
        prod.push_back(new_symbol);
        p->setProd_out(prod);
    }
    prods_alpha.push_back(new Prod({new Symbol("\\L")}));
    if(prods_beta.size() == 0)
    {
        prods_beta.push_back(new Prod({})); // epsilon production
    }
    for(Prod *p : prods_beta)
    {
        vector<Symbol *> prod_beta = p->getProd_out();
        prod_beta.push_back(new_symbol);
        p->setProd_out(prod_beta);
    }
    prods = prods_beta;
    return make_pair(new_symbol,prods_alpha);
}

void LL_Grammar::convert_to_LL_grammmar() {
    unordered_map<Symbol *, vector<Prod *>> production_map;
    vector<Symbol*> nonTerminals;
    unordered_set<Symbol *> nonTerminals_Set;
    for (Production *production : productions)
    {
        production_map[production->getLhs()].push_back(new Prod(production->getRhs()));
        if(nonTerminals_Set.find(production->getLhs()) == nonTerminals_Set.end())
        {
            nonTerminals_Set.insert(production->getLhs());
            nonTerminals.push_back(production->getLhs());
        }
    }
    vector<pair<Symbol *, vector<Prod *>>> rules2add;
    vector<Symbol*> new_nonTerminals;

    bool is_LL = false;
    while (!is_LL)
    {
        is_LL = true;
        for (Symbol* nT : nonTerminals)
        {
            vector<Prod *> prods = production_map[nT];

            for (Symbol *prev_nT : nonTerminals)
            {
                
                if (nT == prev_nT)
                {
                    break;
                }
                vector<Prod *> prev_prods = production_map[prev_nT];
                replace_Symbol(prev_nT, prods, prev_prods);
            }
            new_nonTerminals.push_back(nT);
            pair<Symbol *, vector<Prod *>> new_rule = eliminate_left_recursion(nT, prods);

            production_map[nT] = prods;
            if(new_rule.first != nullptr)
            {
                production_map[new_rule.first] = new_rule.second;
                new_nonTerminals.push_back(new_rule.first);
                is_LL = false;
            }
        }
        nonTerminals = new_nonTerminals;
        new_nonTerminals.clear();
    }
    vector<Production *> new_productions;
    for(Symbol * non_terminal : nonTerminals)
    {
        for(Prod *p : production_map[non_terminal])
        {
            new_productions.push_back(new Production(non_terminal,p->getProd_out()));
        }
    } 
    productions = new_productions;

    
    symbols = unordered_map<string, Symbol*>();
    non_terminal_symbols = unordered_set<Symbol*>();

    for(auto &p : productions){

        Symbol* lhs = p->getLhs();
        symbols.try_emplace(lhs->getName(), lhs);
        for(auto &s : p->getRhs()){
            symbols.try_emplace(s->getName(), s);
        }
    }
    symbols[END_OF_INPUT] = new Symbol(END_OF_INPUT);
    
    for(auto &[_, symbol]: symbols) {
        if(not symbol->getIsTerminal()) non_terminal_symbols.insert(symbol);
    }

    
}