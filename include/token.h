#ifndef TOKEN_H
#define TOKEN_H

// The lexer returns tokens [0-255] if it is an unknown character ie (not defined in the Token enum),otherwise one
// of these for known things.

/*
We also allow Kaleidoscope to call into standard library functions - the LLVM JIT makes this really easy. 
This means that you can use the ‘extern’ keyword to define a function before you use it
(this is also useful for mutually recursive functions).
*/

enum Token{
    tok_eof = -1, // end of file

    // keywords
    tok_def = -2,     
    tok_extern = -3,

    tok_indentifer = -4, //[a-zA-Z][a-zA-Z0-9]*
    tok_number = -5      //[0-9.]+
};

#endif