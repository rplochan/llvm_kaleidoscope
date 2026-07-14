#include <iostream>
#include "lexer.h"
#include "token.h"

int main() {

    while (true) {
        std::string IdentifierStr;
        double NumVal;
        int tok = gettok();

        if (tok == tok_eof)
            break;

        switch (tok) {
        case tok_def:
            std::cout << "DEF\n";
            break;

        case tok_extern:
            std::cout << "EXTERN\n";
            break;

        case tok_identifier:
            std::cout << "IDENTIFIER: " << IdentifierStr << '\n';
            break;

        case tok_number:
            std::cout << "NUMBER: " << NumVal << '\n';
            break;

        default:
            std::cout << "CHAR: " << static_cast<char>(tok) << '\n';
            break;
        }
    }
    return 0;
}