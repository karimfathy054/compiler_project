cmake_minimum_required(VERSION 3.10)

project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)

add_executable(perdictive_parser ParsingTableGenerator.cpp TableEntry.cpp GrammarReader.cpp Production.cpp Symbol.cpp)
