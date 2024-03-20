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
    VariableDeclarator(Node* declarator, Node* initialiser){
        branches.push_back(declarator);
        branches.push_back(initialiser);
    }

    virtual ~VariableDeclarator(){
        for (auto node : branches) {
            delete node;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        branches[0]->EmitRISC(stream, context, destReg);
        branches[1]->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" = "<<std::endl;
        branches[1]->Print(stream);
    }
};

#endif
