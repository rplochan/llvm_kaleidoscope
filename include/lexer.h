#ifndef LEXER_H
#define LEXER_H

#include<string>

extern std::string IdentifierStr; // filled when tok_identifier is present.
extern double NumVal;            // filled when tok_number is present.

int gettok();

#endif 
