#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "node.hpp"

class IntConstant : public Node
{
private:
    int value_;
public:
    IntConstant(int value) : value_(value) {}
    ~IntConstant(){}
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << "li " << context.getRegisterName(destReg)<<", "<< value_ << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << value_;
    }
};

class FloatConstant : public Node
{
private:
    float value;
public:
    FloatConstant(float value_) : value(value_) {}
    ~FloatConstant(){}
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << "li " << context.getRegisterName(destReg)<<", "<< value << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << value;
    }
};

class StringConstant : public Node
{
private:
    char character;
public:
    StringConstant(char character_) : character(character_) {}
    ~StringConstant(){}
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << "li " << context.getRegisterName(destReg)<<", "<< (int)character << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << (int)character;
    }
};
#endif
