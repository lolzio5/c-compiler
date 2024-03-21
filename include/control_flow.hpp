#ifndef CONTROL_FLOW_HPP
#define CONTROL_FLOW_HPP

#include "node.hpp"


class IfStatement : public Node
{
private:
    Node* condition;
    Node* statement;
public:
    IfStatement(Node* condition_, Node* statement_) : condition(condition_), statement(statement_) {}
    ~IfStatement(){
        delete condition;
        delete statement;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int conditionValueRegister = context.findFreeRegister();

        condition->EmitRISC(stream, context, conditionValueRegister);
        std::string falseBranch=context.nameNewBranch();

        stream<<"beq "<<context.getRegisterName(conditionValueRegister)<<", zero, "<<falseBranch<<std::endl;
        statement->EmitRISC(stream, context, destReg);
        stream<<falseBranch<<":"<<std::endl;

        context.freeRegister(conditionValueRegister);
    }
    void Print(std::ostream &stream) const {
        stream<<"if(";
        condition->Print(stream);
        stream<<"){";
        statement->Print(stream);
        stream<<"}"<<std::endl;
    }
};

class IfElseStatement : public Node
{
private:
    Node* condition;
    Node* if_statement;
    Node* else_statement;
public:
    IfElseStatement(Node* condition_, Node* if_statement_, Node* else_statement_) : condition(condition_), if_statement(if_statement_), else_statement(else_statement_) {}
    ~IfElseStatement(){
        delete condition;
        delete if_statement;
        delete else_statement;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int conditionValueRegister = context.findFreeRegister();

        condition->EmitRISC(stream, context, conditionValueRegister);
        std::string falseBranch=context.nameNewBranch();

        std::string continueBranch=context.nameNewBranch();

        stream<<"beq "<<context.getRegisterName(conditionValueRegister)<<", zero, "<<falseBranch<<std::endl;
        if_statement->EmitRISC(stream, context, destReg);
        stream<<"j "<<continueBranch<<std::endl;
        stream<<falseBranch<<":"<<std::endl;
        else_statement->EmitRISC(stream, context, destReg);
        stream<<continueBranch<<":"<<std::endl;
        context.freeRegister(conditionValueRegister);
    }
    void Print(std::ostream &stream) const {
        stream<<"if(";
        condition->Print(stream);
        stream<<"){";
        if_statement->Print(stream);
        stream<<"}"<<std::endl;
        stream<<"else {";
        else_statement->Print(stream);
        stream<<"}"<<std::endl;
    }
};
#endif
