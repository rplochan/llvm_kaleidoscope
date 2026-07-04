#include<token.h>
#include<lexer.h>

#include<string>
#include<cctype>
#include<cstdio>
#include<cstdlib>

extern int gettok(){
   static int LastChar = ' ';

   // skipping white spaces
   while(isspace(LastChar)){
    LastChar = getchar();
   }

   // identifier  [a-zA-Z][a-zA-Z0-9]*
   if(isalpha(LastChar)){
    IdentiferStr = LastChar;
    while(isalnum(LastChar = getchar())){
        IdentiferStr+=LastChar;
    }

    if(IdentiferStr == "def") return tok_def;
    if(IdentiferStr == "extern") return tok_extern;
    return tok_indentifer;
   }

   
    // number: [0-9.]+
   if (isdigit(LastChar) || LastChar == '.') {  
    std::string NumStr;
    do {
        NumStr += LastChar;
        LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

  NumVal = strtod(NumStr.c_str(), 0);
  return tok_number;
}



if (LastChar == '#') {
  // Comment until end of line.
  do
    LastChar = getchar();
  while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

  if (LastChar != EOF)
    return gettok();
}

  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF)
    return tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;

}