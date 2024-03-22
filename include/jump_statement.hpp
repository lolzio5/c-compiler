#ifndef JUMP_STATEMENT_HPP
#define JUMP_STATEMENT_HPP

#include "node.hpp"

class ReturnStatement : public Node
{
private:
    Node *expression_;

public:
    ReturnStatement(Node *expression) : expression_(expression) {}
    ~ReturnStatement()
    {
        delete expression_;
    };

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        if (expression_ != nullptr){
            expression_->EmitRISC(stream, context, destReg);
        }
        if(context.isFunctionCalled()){
            context.uncallFunction();
            stream<<"lw ra, 12(sp)"<<std::endl;
            stream<<"lw s0, 8(sp)"<<std::endl;
            stream<<"addi sp, sp, 16"<<std::endl;
        }
        stream << "jr ra" << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << "return";
        if (expression_ != nullptr){
            stream << " ";
            expression_->Print(stream);
        }
        stream << ";" << std::endl;
    }
};

#endif
