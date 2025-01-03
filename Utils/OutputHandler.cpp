#include "include/OutputHandler.h"

using namespace std;

OutputHandler::OutputHandler(){}

void OutputHandler::add_row_to_output_table(std::stack<Symbol *> st, std::string token, std::string action) {
    string stack_str = get_string_from_stack(st);
    output_table.addRow({stack_str, token, action});
}

void OutputHandler::add_row_to_first_follow_table(std::string name, std::unordered_set<Symbol*> first, std::unordered_set<Symbol*> follow) {
    string first_str = get_string_from_set(first);
    string follow_str = get_string_from_set(follow);
    first_follow_table.addRow({name, first_str, follow_str});
}
void OutputHandler::save_tables() {
    save_first_follow_table(first_follow_filename);
    save_output_table(output_table_filename);
}

void OutputHandler::save_first_follow_table(const std::string& filename) {
    first_follow_table.saveToMarkdown(filename);
}

void OutputHandler::save_output_table(const std::string& filename) {
    output_table.saveToMarkdown(filename);
}

std::string OutputHandler::get_string_from_stack(std::stack<Symbol *> st)
{
    std::string str = "";
    while (!st.empty())
    {
        str = st.top()->getName() + " " + str;
        st.pop();
    }
    return str;
}

std::string OutputHandler::get_string_from_vector(std::vector<Symbol *> vec)
{
    std::string str = "";
    for (auto &s : vec)
    {
        str += s->getName() + " ";
    }
    return str;
}

std::string OutputHandler::get_string_from_set(std::unordered_set<Symbol *> set)
{
    std::string str = "";
    for (auto &s : set)
    {
        if(s->isEpsilon()) {
            str += "epsilon ";
            continue;
        }
        str += s->getName() + " ";
    }
    return str;
}