#pragma once
#include "Production.h"
#include "Symbol.h"
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

void LL_Grammar(vector<Production*> &productions);