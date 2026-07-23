#include"../include/token.h"
#include"../include/lexer.h"
#include"../include/ast.h"
#include<memory>
#include<map>
#include<string>
#include<cctype>
#include<cstdio>
#include<cstdlib>

// CurTok is the current token the parser is using/ viewing.
// getNextToken reads the next Token and update the CurTok
static int CurTok;
static int getNextToken(){
    CurTok = gettok();
    return CurTok;
}

// helper functions...
std::unique_ptr<ast::ExprAST> LogError(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return nullptr;
}

std::unique_ptr<ast::PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

/*it expects to be called when the current token is a tok_number token.
  It takes the current number value, creates a NumberExprAST node,
   advances the lexer to the next token, and finally returns
   the node.
   */
static std::unique_ptr<ast::ExprAST> ParseNumberExpr(){
    auto Result = std::make_unique<ast::NumberExprAST>(NumVal);
    getNextToken();
    return std::move(Result);
}

/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ast::ExprAST> ParseParenExpr(){
    getNextToken(); //eat (.
    auto V = ParseExpression();
    if(!V)
        return nullptr;
    if(CurTok != ')')
        return LogError("expected ')'");
    getNextToken(); //eat ).
    return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ast::ExprAST> ParseIdentifierExpression(){
    std::string IdName = IdentifierStr;
    getNextToken(); //eat identifier.

    if(CurTok != '(')
        return std::make_unique<ast::VariableExprAST>(IdName);

    //call.
    getNextToken(); // eat.
    std::vector<std::unique_ptr<ast::ExprAST>> Args;
    if(CurTok != ')'){
        while(true){
            if(auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;

            if(CurTok == ')')
                break;
            if(CurTok != ',')
                return LogError("expected ')' or ','");
            getNextToken(); // eat ','.
        }
    }
    getNextToken();  // eat ')'.
    return std::make_unique<ast::CallExprAST>(IdName, std::move(Args));
}

static std::unique_ptr<ast::ExprAST> ParsePrimary(){
    switch (CurTok) {
        case tok_identifier:
        return ParseIdentifierExpression();

        case tok_number:
        return ParseNumberExpr();

        case '(':
        return ParseParenExpr();

        default:
        return LogError("unknown token while expecting expression.");
    }
}

// operator-precedence parsing....
// binary exp parsing..

// BinopPrecedence - holds the precedence for each binary operator that is defined.
static std::map<char,int> BinopPrecedence;
// GetTokPrecendence- Get the precedence of pending binary operator token.
static int GetTokPrecedence(){
    if(!isascii(CurTok)){
        return -1;
    }

    int TokPrec = BinopPrecedence[CurTok];
    if(TokPrec <= 0) return -1;  // because the lowest precedence is 1.
    return TokPrec;
}
