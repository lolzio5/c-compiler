#ifndef TYPE_SPECIFIER
#define TYPE_SPECIFIER

#include "node.hpp"

class TypeSpecifier : public Node
{
private:
    std::string type_;

public:
    TypeSpecifier(std::string type) : type_(type){};
    ~TypeSpecifier(){};
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const override {};
    void Print(std::ostream &stream) const {
        stream << type_;
    }
};

#endif
