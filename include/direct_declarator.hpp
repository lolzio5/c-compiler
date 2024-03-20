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
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        identifier_->EmitRISC(stream, context, destReg);
        stream << ":" << std::endl;
    };
    void Print(std::ostream &stream) const {
        identifier_->Print(stream);
    };
};

#endif
