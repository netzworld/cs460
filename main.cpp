#include <iostream>
#include<vector>


#include "Token.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;

    inputStream.open(argv[1], std::ios::in);
    if (!inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(2);
    }

// this basically just says this file has not been tokenized yet, and sets the file up to be tokenized
    Tokenizer tokenizer(inputStream); 
     // This also sets up the file.
    Parser parser(tokenizer);

    // this calls the get token stuff. Each line is looking for assignment statements basically.
    // the first thing on each line is supposed to be a name, then it evaluates the rest of the line.
    Statements *statements = parser.statements();

    // because the parser.statements() ungets the last token, it should have a eof token left. otherwise it is a messup
    Token lastToken = tokenizer.getToken();
    if (!lastToken.eof()) {
        std::cout << "Unexpected token in input." << std::endl;
        lastToken.print();
        exit(1);
    }
    SymTab symTab;

    statements->print();
    statements->evaluate(symTab);
    // std::cout << std::endl << "Symbol table contains the following variables.\n";
    // symTab.print();

    return 0;
}
