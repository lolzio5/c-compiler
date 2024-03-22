#ifndef MULTI_DECLARATION_HPP
#define MULTI_DECLARATION_HPP

#include "node.hpp"
#include "context.hpp"

class MultiDeclarator : public Node
{
private:
    Node *specifier;
    Node *declarator;
public:
    MultiDeclarator(Node* specifier_, Node* declarator_) : specifier(specifier_), declarator(declarator_){}

    virtual ~MultiDeclarator(){
        delete declarator;
        delete specifier;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        if(declarator!=nullptr){
            declarator->EmitRISC(stream, context, destReg);
        }
        specifier->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        specifier->Print(stream);
        if(declarator!=nullptr){
            declarator->Print(stream);
        }
    }
};

#endif
