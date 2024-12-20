#pragma once

#include <string>
#include "lexica.cpp"

using namespace std;

class InputParser{
    public:
    string grammerFilePath;
    string inputFilePath;
    lexical_analyzer lexica; // to get tokens one by one
    public:
    InputParser(string grammerFilePath, string inputFilePath);
    
};