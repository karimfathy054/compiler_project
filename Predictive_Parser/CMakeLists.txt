add_library(Predictive_Parser GrammarReader.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp FirstFollowGen.cpp)

add_executable(PP GrammarReader.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp FirstFollowGen.cpp)