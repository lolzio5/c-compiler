#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "node.hpp"

class IntConstant : public Node
{
private:
    int value_;
public:
    IntConstant(int value) : value_(value) {}

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << "li " << context.getRegisterName(destReg)<<", "<< value_ << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << value_;
    }
};
#endif
