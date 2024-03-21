#ifndef VARIABLE_DECLARATOR_HPP
#define VARIABLE_DECLARATOR_HPP

#include "node.hpp"
#include "context.hpp"

class VariableDeclarator : public Node
{
private:
    Node *declarator;
    Node *initialiser;
public:
    VariableDeclarator(Node* declarator_, Node* initialiser_) : declarator(declarator_), initialiser(initialiser_){}

    virtual ~VariableDeclarator(){
        delete declarator;
        delete initialiser;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{
        if (initialiser!=nullptr){
            declarator->EmitRISC(stream, context, destReg);
            initialiser->EmitRISC(stream, context, destReg);
        }
        else{
            declarator->EmitRISC(stream, context, destReg);
        }
    }
    void Print(std::ostream &stream) const {
        if (initialiser!=nullptr){
            declarator->Print(stream);
            stream<<" = "<<std::endl;
            initialiser->Print(stream);
        }
        else{
            declarator->Print(stream);
        }

        stream << ";" << std::endl;

    }
};

class VariableAssignExpression : public Node
{
private:
    Node *unary_expression;
    Node *assignement_expression;
public:
    VariableAssignExpression(Node* unary_expression_, Node* assignement_expression_) : unary_expression(unary_expression_), assignement_expression(assignement_expression_){}

    virtual ~VariableAssignExpression(){
        delete unary_expression;
        delete assignement_expression;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const{

        unary_expression->EmitRISC(stream, context, destReg);
        assignement_expression->EmitRISC(stream, context, destReg);

        std::string variableName = unary_expression->GetIdentifier();

        std::string variableType;
        int currentStackLocation;
        if (context.variableLocation(variableName)==-1){
            currentStackLocation=context.bindVariable(variableName, variableType);
            variableType="double";
        }
        else{
            currentStackLocation=context.variableLocation(variableName);
            variableType = context.getVariableType(variableName);
        }

        if (variableType=="float"){
            stream<<"fsw f"<<context.getRegisterName(destReg)<<", " <<currentStackLocation<<"(s0)"<<std::endl;
        }
        else if(variableType=="double"){
            stream<<"fsd f"<<context.getRegisterName(destReg)<<", " <<currentStackLocation<<"(s0)"<<std::endl;
        }
        else{
            stream<<"sw "<<context.getRegisterName(destReg)<<", "<<currentStackLocation<<"(s0)"<<std::endl;
        }
    }
    void Print(std::ostream &stream) const {
        unary_expression->Print(stream);
        stream<<" = ";
        assignement_expression->Print(stream);
    }
};

#endif
