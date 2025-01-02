#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H
#include "MarkdownTable.h"
#include <iostream>
#include <stack>
#include "Predictive_Parser/include/Symbol.h"
#include <unordered_set>

class OutputHandler {
    public:
        OutputHandler();
        std::string first_follow_filename = "../output_first_follow.md"; 
        std::string output_table_filename = "../output_table.md";
        MarkdownTable first_follow_table = MarkdownTable({"Symbol", "First", "Follow"});
        MarkdownTable output_table = MarkdownTable({"Stack", "Curr Input Token", "Action"});
        void add_row_to_output_table(std::stack<Symbol *> st, std::string token, std::string action);
        void add_row_to_first_follow_table(std::string name, std::unordered_set<Symbol*> first, std::unordered_set<Symbol*> follow);
        void save_tables();
    private:
        void save_first_follow_table(const std::string& filename);
        void save_output_table(const std::string& filename);
        std::string get_string_from_stack(std::stack<Symbol *> st);
        std::string get_string_from_vector(std::vector<Symbol *> vec);
        std::string get_string_from_set(std::unordered_set<Symbol *> set);
};
#endif