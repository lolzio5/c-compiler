#ifndef VARIABLE_DECLARATOR_HPP
#define VARIABLE_DECLARATOR_HPP

#include "node.hpp"
#include "context.hpp"

class VariableDeclarator : public Node
{
private:
    Node *declarator;
    Node *initialiser;
public:
    VariableDeclarator(Node* declarator_, Node* initialiser_) : declarator(declarator_), initialiser(initialiser_){}

    virtual ~VariableDeclarator(){
        delete declarator;
        delete initialiser;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        initialiser->EmitRISC(stream, context, destReg);
        declarator->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        initialiser->Print(stream);
        stream<<" = "<<std::endl;
        declarator->Print(stream);
    }
};

#endif
