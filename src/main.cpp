#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

#include "Tokenizer.cpp"
#include "Parser.cpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect Usage. You can only pass one source file" << std::endl;
        return EXIT_FAILURE;
    }

    char character;

    // Read from the text file
    std::ifstream MyReadFile(argv[1]);

    //save text file stream
    std::stringstream srcStream;
    srcStream << MyReadFile.rdbuf();

    // Close the file
    MyReadFile.close();

    std::stringstream ss;
    Tokenizer tokenizer;
    Parser parser;

    while (srcStream.get(character)) {
        if (character != ';') {
            ss << character;
        } else {
            ss << character;

            // std::cout << ss.str() << std::endl;
            tokenizer.setSource(ss.str());
            parser.setTokens(tokenizer.tokenize());
            parser.parseStmt();

            ss.str("");
            ss.clear();
        }
    }

    return EXIT_SUCCESS;
}
