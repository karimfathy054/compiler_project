#ifndef MARKDOWNTABLE_H
#define MARKDOWNTABLE_H

#include <iostream>
#include <vector>
#include <string>

class MarkdownTable {
public:
    MarkdownTable(const std::vector<std::string>& colNames);
    void addRow(std::vector<std::string> row);
    void saveToMarkdown(const std::string& filename) const;
private:
    std::vector<std::string> columnNames;
    std::vector<std::vector<std::string>> tableData;

    std::vector<size_t> calculateColumnWidths() const;
    
    void writeHeader(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const;

    void writeSeparator(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const;

    void writeDataRows(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const;
};

#endif // MARKDOWNTABLE_H
