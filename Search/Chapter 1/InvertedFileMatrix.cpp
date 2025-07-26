//
// Created by Oscar Abreu on 7/25/25.
//

std::string readFileContents(std::string filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer;
}

std::vector<std::string> tokenize(const std::string contents) {
    std::vector<std::string> tokens;
    std::string temporary;

    for (const auto& c : contents) {
        if (isalnum(c)) temporary += (to_lower(c));
        else if (!temporary.empty()) {
            tokens.push_back(temporary);
            temporary.clear();
        }
    }
    if (!temporary.empty()) tokens.push_back(temporary);
    return tokens;
}

int main() {
     InvertedIndex ii;
      std::string folderPath = "./docs";
      for (const auto& file :: std::filesystem::directory_iterator(folderPath)) {
            if (file.extension().string() == ".txt") {
                std::string fileName = file.path().filename().string();
                std::string contents = readFileContents(file.content().string());
                std::vector<std::string> tokens = tokenize(contents);
                ii.AddDocument(fileName, tokens);
               }
      }
      ii.PrintMatrixToCMDL("ii.txt");
}