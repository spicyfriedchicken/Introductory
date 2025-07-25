//
// Created by Oscar Abreu on 7/24/25.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>

class TermDocumentMatrix {
public:
    std::unordered_map<std::string, int> termToRow;
    std::vector<std::string> documents;
    std::vector<std::vector<int>> matrix; // matrix[term][doc] = frequency

    void addDocument(const std::string& docId, const std::vector<std::string>& tokens) {
        int docIndex = documents.size();
        documents.push_back(docId);

        for (auto& row : matrix) {
            row.resize(documents.size(), 0);
        }

        for (const auto& token : tokens) {
            int row;
            if (termToRow.count(token) == 0) {
                row = matrix.size();
                termToRow[token] = row;
                matrix.emplace_back(documents.size(), 0);
            } else {
                row = termToRow[token];
            }
            matrix[row][docIndex]++;
        }
    }

    void printMatrixToFile(const std::string& path) const {
        std::ofstream out(path);
        out << std::setw(20) << "TERM";
        for (const auto& doc : documents) {
            out << std::setw(15) << doc;
        }
        out << "\n";

        for (const auto& [term, row] : termToRow) {
            out << std::setw(20) << term;
            for (int count : matrix[row]) {
                out << std::setw(15) << count;
            }
            out << "\n";
        }
    }
};

std::string readFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string current;

    for (char c : text) {
        if (isalnum(c)) current += std::tolower(c);
        else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }
    if (!current.empty()) tokens.push_back(current);
    return tokens;
}

int main() {
    TermDocumentMatrix tdm;
    std::string folderPath = "docs/";
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            std::string fileName = entry.path().filename().string();
            std::string content = readFileContent(entry.path().string());
            std::vector<std::string> tokens = tokenize(content);
            tdm.addDocument(fileName, tokens);
        }
    }

    tdm.printMatrixToFile("TDM.txt");
}