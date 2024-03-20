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

    void EmitRISC(std::ostream &stream, Context &context) const{
        branches[0]->EmitRISC(stream, context);
        branches[1]->EmitRISC(stream, context);
    }
    void Print(std::ostream &stream) const {
        stream<<"Assign Variable"<<std::endl;
    }
};

#endif
