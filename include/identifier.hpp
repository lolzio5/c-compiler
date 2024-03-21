#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include "node.hpp"

class FunctionIdentifier : public Node
{
private:
    std::string identifier_;

public:
    FunctionIdentifier(std::string identifier) : identifier_(identifier){};
    ~FunctionIdentifier(){};
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
       stream << identifier_;
    }
    void Print(std::ostream &stream) const {
        stream << identifier_;
    }

    std::string GetIdentifier() const{
        return identifier_;
    }
};

class VariableIdentifier : public Node
{
private:
    std::string identifier_;

public:
    VariableIdentifier(std::string identifier) : identifier_(identifier){};
    ~VariableIdentifier(){};
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int currentStackLocation = context.variableLocation(identifier_);
        if (currentStackLocation!=-1){
            std::string variableType=context.getVariableType(identifier_);
            if(variableType=="double"){
                stream<<"fld f"<<context.getRegisterName(destReg)<<", "<<currentStackLocation<< "(s0)"<<std::endl;
            }
            else if (variableType=="float"){
                stream<<"flw f"<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
            }
            else{
                stream<<"lw "<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
            }
        }
    }
    void Print(std::ostream &stream) const {
        stream << identifier_;
    }
    std::string GetIdentifier() const{
        return identifier_;
    }
};

#endif
