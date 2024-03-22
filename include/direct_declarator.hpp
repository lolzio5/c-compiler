#ifndef DIRECT_DECLARATOR_HPP
#define DIRECT_DECLARATOR_HPP

#include "node.hpp"

class DirectDeclarator : public Node
{
private:
    Node *identifier_;

public:
    DirectDeclarator(Node *identifier) : identifier_(identifier){};
    ~DirectDeclarator()
    {
        delete identifier_;
    }
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        if(identifier_!=nullptr){
            std::string functionName=identifier_->GetIdentifier();
            if(context.isFunctionDeclared(functionName)==true){
                context.callFunction();
                stream<<"addi sp,sp,-16"<<std::endl;
                stream<<"sw ra,12(sp)"<<std::endl;
                stream<<"sw s0,8(sp)"<<std::endl;
                stream<<"addi s0,sp,16"<<std::endl;
                stream<<"call "<<functionName<<std::endl;
            }
            else{
                context.declareFunction(functionName);
                stream << ".globl ";
                identifier_->EmitRISC(stream, context, destReg);
                stream<<std::endl;
                identifier_->EmitRISC(stream, context, destReg);
                stream << ":" << std::endl;
            }
        }
    }
    void Print(std::ostream &stream) const {
        identifier_->Print(stream);
    }
};
#endif
