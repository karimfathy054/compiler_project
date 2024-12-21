cmake_minimum_required(VERSION 3.10)
project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)


add_subdirectory(Lexical_analyzer)
add_subdirectory(Predictive_Parser)

# add_executable(compiler main.cpp)
add_executable(compiler main.cpp input_parser.cpp)

target_link_libraries(compiler PUBLIC Predictive_Parser Lexical_analyzer)
target_include_directories(compiler PRIVATE Lexical_analyzer Predictive_Parser)

# target_include_directories(perdictive_parser PRIVATE Predictive_Parser)