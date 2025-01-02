#include "include/MarkdownTable.h"
#include <fstream>
#include <iomanip>

MarkdownTable::MarkdownTable(const std::vector<std::string>& colNames)
    : columnNames(colNames) {}

void MarkdownTable::addRow(std::vector<std::string> row) {
    this->tableData.push_back(row);
}

void MarkdownTable::saveToMarkdown(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Calculate the column widths based on the longest value
    std::vector<size_t> columnWidths = calculateColumnWidths();
    
    writeHeader(outFile, columnWidths);

    writeSeparator(outFile, columnWidths);

    writeDataRows(outFile, columnWidths);

    outFile.close();
    std::cout << "Output table saved to " << filename << std::endl;
}

// Function to calculate the maximum width for each column
std::vector<size_t> MarkdownTable::calculateColumnWidths() const {
    size_t cols = columnNames.size();
    std::vector<size_t> columnWidths(cols, 0);

    // Find the maximum width for each column (names + data)
    for (size_t col = 0; col < cols; ++col) {
        columnWidths[col] = columnNames[col].length();  // Column name length

        for (const auto& row : tableData) {
            columnWidths[col] = std::max(columnWidths[col], row[col].length());
        }
    }

    return columnWidths;
}

// Write the header row with column names
void MarkdownTable::writeHeader(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const {
    outFile << "|";
    for (size_t col = 0; col < columnWidths.size(); ++col) {
        outFile << " " << std::setw(columnWidths[col]) << columnNames[col] << " |";
    }
    outFile << "\n";
}

// Write the separator row (lines under the header)
void MarkdownTable::writeSeparator(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const {
    outFile << "|";
    for (size_t col = 0; col < columnWidths.size(); ++col) {
        outFile << std::string(columnWidths[col] + 2, '-') << "|";
    }
    outFile << "\n";
}

// Write the data rows
void MarkdownTable::writeDataRows(std::ofstream& outFile, const std::vector<size_t>& columnWidths) const {
    for (const auto& row : tableData) {
        outFile << "|";
        for (size_t col = 0; col < row.size(); ++col) {
            outFile << " " << std::setw(columnWidths[col]) << row[col] << " |";
        }
        outFile << "\n";
    }
}
