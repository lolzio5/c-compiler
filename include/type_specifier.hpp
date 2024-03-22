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
    std::string GetType() const{
        return type_;
    }
};

class SizeOf : public Node
{
private:
    Node* expression;
public:
    SizeOf(Node* expression_) : expression(expression_){};
    ~SizeOf(){};
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        std::string variableType = context.getVariableType(expression->GetIdentifier());
        int variableSize;
        if (variableType=="int"){
            variableSize=4;
        }
        else if (variableType=="float"){
            variableSize=4;
        }
        else if (variableType=="double"){
            variableSize=8;
        }
        else if (variableType=="char"){
            variableSize=1;
        }
        else if (variableType=="short"){
            variableSize=2;
        }
        else if (variableType=="long"){
            variableSize=4;
        }
        else if (variableType=="void"){
            variableSize=0;
        }
        else if (variableType=="char"){
            variableSize=1;
        }
        stream << "li " << context.getRegisterName(destReg) << ", " << variableSize << std::endl;
    }
    void Print(std::ostream &stream) const {
        stream << "sizeof(";
        expression->Print(stream);
        stream<<");"<<std::endl;
    }
};

#endif
