cmake_minimum_required(VERSION 3.5.0)
project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)


add_executable(compiler_project main.cpp)
add_executable(ruleReader RulesReader.cpp)
add_executable(nfaGen NFAGenerator.cpp NFA.cpp)
