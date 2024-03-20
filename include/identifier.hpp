#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include "node.hpp"

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string identifier) : identifier_(identifier){};
    ~Identifier(){};
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << identifier_;
    }
    void Print(std::ostream &stream) const {
        stream << identifier_;
    };
};

#endif
