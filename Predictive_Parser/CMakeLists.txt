add_library(Predictive_Parser GrammarReader2.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp)

add_executable(PP GrammarReader2.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp)