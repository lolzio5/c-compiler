#ifndef MULTI_DECLARATION_HPP
#define MULTI_DECLARATION_HPP

#include "node.hpp"
#include "context.hpp"

class MultiDeclarator : public Node
{
private:
    Node *specifier;
    Node *declarator;
public:
    MultiDeclarator(Node* specifier_, Node* declarator_) : specifier(specifier_), declarator(declarator_){}

    virtual ~MultiDeclarator(){
        delete declarator;
        delete specifier;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        if(declarator!=nullptr){
            declarator->EmitRISC(stream, context, destReg);
        }
        if(specifier!=nullptr){
            specifier->EmitRISC(stream, context, destReg);
        }

    }
    void Print(std::ostream &stream) const {
        if(specifier!=nullptr){
            specifier->Print(stream);
        }
        if(declarator!=nullptr){
            declarator->Print(stream);
        }
    }
};

class SingleDeclarator : public Node
{
private:
    Node *specifier;
    Node *declarator;
public:
    SingleDeclarator(Node* specifier_, Node* declarator_) : specifier(specifier_), declarator(declarator_){}

    virtual ~SingleDeclarator(){
        delete specifier;
        delete declarator;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        std::string variableType = specifier->GetType();
        std::string variableName = declarator->GetIdentifier();
        int currentStackLocation = context.bindVariable(variableName, variableType);
        if(variableType=="float"){
            stream<<"fsw f"<<context.getRegisterName(destReg)<<", " <<currentStackLocation<<"(s0)"<<std::endl;
        }
        else if(variableType=="double"){
            stream<<"fsd f"<<context.getRegisterName(destReg)<<", " <<currentStackLocation<<"(s0)"<<std::endl;
        }
        else if(variableType=="int"){
            stream<<"sw "<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
        }
        else if(variableType=="char"){
            stream<<"sb "<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
        }
    }
    void Print(std::ostream &stream) const {
        specifier->Print(stream);
        declarator->Print(stream);
    }
};

#endif
