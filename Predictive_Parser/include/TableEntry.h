#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include "Symbol.h"


class TableEntry{
    
    bool isSync;
    Production *production;
    public:
    TableEntry(); //creating a table for sync ,error is throwed if the entry is null not when the entry is accessed
    TableEntry(bool isSync);
    TableEntry(Production *production);
    bool getIsSync();
    Production* getProduction();
};

#endif // TABLEENTRY_H