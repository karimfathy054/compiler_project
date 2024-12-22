cmake_minimum_required(VERSION 3.10)

# Create a static library for Lexical_analyzer
add_library(Lexical_analyzer STATIC lexica.cpp DFAGenerator.cpp DFADecoder.cpp DFAMinimizerPartitioning.cpp DFAState.cpp NFA.cpp NFAGenerator.cpp RulesReader.cpp State.cpp)

# Include directories for Lexical_analyzer
target_include_directories(Lexical_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})