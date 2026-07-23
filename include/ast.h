#ifndef AST_H
#define AST_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
// ast - abstract syntax tree...
// the output of the parser.

// input->(tokens) -> parser ->(ast) output.

namespace ast{

    // base class for all the nodes
    class ExprAST{
    public:
        virtual ~ExprAST() {}
    };

    // expression class for numeric litrals...
    class NumberExprAST: public ExprAST{
    private:
        double Val;
    public:
        NumberExprAST(double Val): Val(Val){}
    };

    // expression class for variables..
    class VariableExprAST: public ExprAST{
    private:
        std::string Name;
    public:
        VariableExprAST(const std::string &Name): Name(Name){}
    };

    // expression class for binary operators..
    class BinaryExprAST: public ExprAST{
    private:
        char Op;
        std::unique_ptr<ExprAST> LHS;
        std::unique_ptr<ExprAST> RHS;

    public:
        BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
        std::unique_ptr<ExprAST> RHS):Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

    // expression for function calls
   class CallExprAST : public ExprAST {
    private:
      std::string Callee;
      std::vector<std::unique_ptr<ExprAST>> Args;

    public:
        CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
            : Callee(Callee), Args(std::move(Args)) {}
    };


     // Function signature ...
    class PrototypeAST{
    private:
        std::string Name;
        std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args): Name(Name),
            Args(std::move(Args)) {}

        const std::string &getName() const {return Name; }

    };


    // Function definition...
    class FunctionAST{
    private:
        std::unique_ptr<PrototypeAST> Proto;
        std::unique_ptr<ExprAST> Body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body):
            Proto(std::move(Proto)), Body(std::move(Body)){}
    };

}

#endif
