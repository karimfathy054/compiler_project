# add_library(Predictive_Parser GrammarReader2.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp FirstFollowGen.cpp)

# add_executable(PP GrammarReader.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp FirstFollowGen.cpp Left_Factoring.cpp PrefixTree.cpp)

cmake_minimum_required(VERSION 3.10)

# Create a static library for Predictive_parser
add_library(Predictive_parser STATIC GrammarReader.cpp LL_Grammar.cpp ParsingTableGenerator.cpp Production.cpp Symbol.cpp TableEntry.cpp FirstFollowGen.cpp Left_Factoring.cpp PrefixTree.cpp)

# Include directories for Predictive_parser
target_include_directories(Predictive_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
