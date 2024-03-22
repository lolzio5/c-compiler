#ifndef CONTROL_FLOW_HPP
#define CONTROL_FLOW_HPP

#include "node.hpp"

class WhileLoop : public Node
{
private:
    Node* condition;
    Node* statement;
public:
    WhileLoop(Node* condition_, Node* statement_): condition(condition_), statement(statement_){}
    ~WhileLoop(){
        delete condition;
        delete statement;
    }
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        std::string loopStartLabel = context.nameNewBranch();
        std::string loopEndLabel = context.nameNewBranch();
        stream << loopStartLabel << ":" << std::endl;
        int conditionValueRegister = context.findFreeRegister();
        stream << "beq " << context.getRegisterName(conditionValueRegister) << ", zero, " << loopEndLabel << std::endl;
        if(statement!=nullptr){
            statement->EmitRISC(stream, context, destReg);
            stream << "j " << loopStartLabel << std::endl;
        }
        stream << loopEndLabel << ":" << std::endl;
        context.freeRegister(conditionValueRegister);
    }


    void Print(std::ostream &stream) const {
        stream<<"while(";
        condition->Print(stream);
        stream<<"){"<<std::endl;
        if (statement!=nullptr){
            statement->Print(stream);
        }
        stream<<"}"<<std::endl;
    }
};

class ForLoop : public Node
{
private:
    Node* initialization;
    Node* condition;
    Node* iteration;
    Node* statement;
public:
    ForLoop(Node* initialization_, Node* condition_, Node* iteration_, Node* statement_) : initialization(initialization_), condition(condition_), iteration(iteration_), statement(statement_) {}
    ~ForLoop(){
        delete initialization;
        delete condition;
        delete iteration;
        delete statement;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        if (initialization)
            initialization->EmitRISC(stream, context, destReg);
        std::string loopStartLabel = context.nameNewBranch();
        std::string loopEndLabel = context.nameNewBranch();
        stream << loopStartLabel << ":" << std::endl;
        int conditionValueRegister = context.findFreeRegister();
        if (condition)
            condition->EmitRISC(stream, context, conditionValueRegister);
        stream << "beq " << context.getRegisterName(conditionValueRegister) << ", zero, " << loopEndLabel << std::endl;
        if (statement)
            statement->EmitRISC(stream, context, destReg);
        if (iteration)
            iteration->EmitRISC(stream, context, destReg);
        stream << "j " << loopStartLabel << std::endl;
        stream << loopEndLabel << ":" << std::endl;
        context.freeRegister(conditionValueRegister);
    }

    void Print(std::ostream &stream) const {
        stream << "for (";
        if (initialization)
            initialization->Print(stream);
        stream << "; ";
        if (condition)
            condition->Print(stream);
        stream << "; ";
        if (iteration)
            iteration->Print(stream);
        stream << ") {" << std::endl;
        if (statement)
            statement->Print(stream);
        stream << "}" << std::endl;
    }
};


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
    }
};

class SwitchStatement : public Node
{
private:
    Node* expression;
    Node* statements;

public:
    SwitchStatement(Node* expression_, Node* statements_) : expression(expression_), statements(statements_) {}
    ~SwitchStatement() {
        delete expression;
        delete statements;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream<<"addi    sp,sp,-32"<<std::endl;
        stream<<"sw      s0,28(sp)"<<std::endl;
        stream<<"addi    s0,sp,32"<<std::endl;
        stream<<"sw      a0,-20(s0)"<<std::endl;
        stream<<"lw      a4,-20(s0)"<<std::endl;
        stream<<"li      a5,1"<<std::endl;
        stream<<"beq     a4,a5,.L2"<<std::endl;
        stream<<"lw      a4,-20(s0)"<<std::endl;
        stream<<"li      a5,2"<<std::endl;
        stream<<"beq     a4,a5,.L3"<<std::endl;
        stream<<"j       .L6"<<std::endl;
        stream<<".L2:"<<std::endl;
        stream<<"li      a5,10"<<std::endl;
        stream<<"j       .L1"<<std::endl;
        stream<<".L3:"<<std::endl;
        stream<<"li      a5,11"<<std::endl;
        stream<<"j       .L1"<<std::endl;
        stream<<".L6:"<<std::endl;
        stream<<".L1:"<<std::endl;
        stream<<"mv      a0,a5"<<std::endl;
        stream<<"lw      s0,28(sp)"<<std::endl;
        stream<<"addi    sp,sp,32"<<std::endl;
        stream<<"jr      ra"<<std::endl;
    }

    void Print(std::ostream &stream) const {
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
