#include "include/GrammerReader.h"

class PredictiveParserGen {
public:
    PredictiveParserGen() {
        GrammarReader reader("ll_grammar.txt");
        std::vector<GrammarReader::Production> productions = reader.getProductions();
    }
};