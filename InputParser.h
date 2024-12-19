#pragma once

#include <string>
#include "lexica.h"

using namespace std;

class InputParser{
    public:
    string grammerFilePath;
    string inputFilePath;
    lexical_analyzer lexica;
    public:
    InputParser(string grammerFilePath, string inputFilePath);

};