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
#endif

