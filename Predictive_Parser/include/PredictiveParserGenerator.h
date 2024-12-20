#ifndef PREDICTIVEPARSERGENERATOR_H
#define PREDICTIVEPARSERGENERATOR_H

#include <unordered_map>
#include <string>
#include "Symbol.h"
using namespace std;


unordered_map<pair<string, string>, vector<Symbol*>> generatePredictiveParserTable(string grammerFilePath); //return predictive parser table

#endif // PREDICTIVEPARSERGENERATOR_H