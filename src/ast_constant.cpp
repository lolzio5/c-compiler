#include "ast_constant.hpp"

void IntConstant::EmitRISC(std::ostream &stream, Context &context) const
{
    stream << "li a0, " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}


// void DoubleConstant::EmitRISC(std::ostream &stream, Context &context) const
//{
   // stream << "addi a0, zero, " << value_ << std::endl;
   // stream << "fcvt.s.w ft0, a0"<< std::endl;
//}

//void DoubleConstant::Print(std::ostream &stream) const
//{
 //   stream << "addi a0, zero, " << value_ << std::endl;
 //   stream << value_;
//}

// void FloatConstant::EmitRISC(std::ostream &stream, Context &context) const
// {
//     stream << "addi a0, zero, " << value_ << std::endl;
//     stream << "fcvt.s.w ft0, a0"<< std::endl;
// }

// void FloatConstant::Print(std::ostream &stream) const
// {
//     stream << "addi a0, zero, " << value_ << std::endl;
//     stream << value_;
// }
