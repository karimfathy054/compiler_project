#include "include/TableEntry.h"

TableEntry::TableEntry(){
    this->isSync = true;
    this->production = nullptr;
}

TableEntry::TableEntry(Production *production){
    this->isSync = false;
    this->production = production;
}

bool TableEntry::getIsSync(){
    return this->isSync;
}

Production* TableEntry::getProduction(){
    return this->production;
}


