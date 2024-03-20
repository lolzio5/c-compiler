#ifndef AST_CONSTANT_HPP
#define AST_CONSTANT_HPP

#include "node.hpp"

class IntConstant : public Node
{
private:
    int value_;
public:
    IntConstant(int value) : value_(value) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

// class DoubleConstant : public Node
// {
// private:
//     double value_;
// public:
//     DoubleConstant(double value) : value_(value) {}

//     void EmitRISC(std::ostream &stream, Context &context) const override;
//     void Print(std::ostream &stream) const override;
// };

// class FloatConstant : public Node
// {
// private:
//     float value_;
// public:
//     FloatConstant(float value) : value_(value) {}

//     void EmitRISC(std::ostream &stream, Context &context) const override;
//     void Print(std::ostream &stream) const override;
// };
#endif
