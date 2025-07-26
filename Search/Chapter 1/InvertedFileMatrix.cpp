//
// Created by Oscar Abreu on 7/25/25.
//

int main() {
    InvertedIndex ii;
    std::string folderPath = "docs/";
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            std::string fileName = entry.path().filename().string();
            std::string content = readFileContent(entry.path().string());
            std::vector<std::string> tokens = tokenize(content);
            ii.addDocument(fileName, tokens);
        }
    }
    ii.printMatrixToFile("ii.txt");
}