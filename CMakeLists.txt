cmake_minimum_required(VERSION 3.10)

project(compiler_project VERSION 0.1.0 LANGUAGES C CXX)

# Add subdirectories
add_subdirectory(Lexical_analyzer)
add_subdirectory(Predictive_Parser)

# Add the main executable
add_executable(main main.cpp Utils/Compiler.cpp Utils/MarkdownTable.cpp Utils/OutputHandler.cpp)

# Link the libraries
target_link_libraries(main Lexical_analyzer Predictive_parser)