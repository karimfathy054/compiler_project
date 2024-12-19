cmake_minimum_required(VERSION 3.10)
project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)


add_subdirectory(Lexical_analyzer)

add_executable(compiler main.cpp)

# target_link_libraries(compiler PRIVATE lexical_analyzer)
target_include_directories(compiler PRIVATE Lexical_analyzer)