#ifndef FUNCTION_CALLER_HPP
#define FUNCTION_CALLER_HPP

#include "node.hpp"

class FunctionCall : public Node
{
private:
    Node *expression;

public:
    FunctionCall(Node *expression_) : expression(expression_){};
    ~FunctionCall()
    {
        delete expression;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        std::string functionName=expression->GetIdentifier();
        context.callFunction();
        stream<<"addi sp,sp,-16"<<std::endl;
        stream<<"sw ra,12(sp)"<<std::endl;
        stream<<"sw s0,8(sp)"<<std::endl;
        stream<<"addi s0,sp,16"<<std::endl;
        stream<<"call "<<functionName<<std::endl;
    }
    void Print(std::ostream &stream) const {
        std::string functionName=expression->GetIdentifier();
        stream<<functionName<<"()"<<std::endl;
    }
};

class FunctionCallWithArguments : public Node
{
private:
    Node *expression;
    Node *arguments;

public:
    FunctionCallWithArguments(Node *expression_, Node *arguments_) : expression(expression_), arguments(arguments_){};
    ~FunctionCallWithArguments()
    {
        delete expression;
        delete arguments;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        std::string functionName=expression->GetIdentifier();
        context.callFunction();
        arguments->EmitRISC(stream, context, destReg);
        stream<<"addi sp,sp,-16"<<std::endl;
        stream<<"sw ra,12(sp)"<<std::endl;
        stream<<"sw s0,8(sp)"<<std::endl;
        stream<<"addi s0,sp,16"<<std::endl;
        stream<<"call "<<functionName<<std::endl;
    }
    void Print(std::ostream &stream) const {

    }
};


#endif
