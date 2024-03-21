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
            stream<<"lw "<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
        }
        else{
            std::string variableName = identifier_;
            int variableAddress = context.bindVariable(variableName);
            int variableRegister = context.findFreeRegister();
            stream<<"sw "<<context.getRegisterName(variableRegister)<<", "<<variableAddress<<"(s0)"<<std::endl;
            context.freeRegister(variableRegister);
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
