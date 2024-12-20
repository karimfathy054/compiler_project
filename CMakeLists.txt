cmake_minimum_required(VERSION 3.10)
project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)


add_subdirectory(Lexical_analyzer)
add_subdirectory(Predictive_Parser)

# target_include_directories(lexiacal_analyzer PRIVATE Lexical_analyzer)
target_include_directories(perdictive_parser PRIVATE Predictive_Parser)