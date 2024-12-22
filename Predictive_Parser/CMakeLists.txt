# add_library(Predictive_Parser GrammarReader2.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp)

# add_executable(PP GrammarReader2.cpp Production.cpp Symbol.cpp TableEntry.cpp ParsingTableGenerator.cpp)

cmake_minimum_required(VERSION 3.10)

# Create a static library for Predictive_parser
add_library(Predictive_parser STATIC GrammarReader.cpp LL_Grammar.cpp ParsingTableGenerator.cpp Production.cpp Symbol.cpp TableEntry.cpp)

# Include directories for Predictive_parser
target_include_directories(Predictive_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
