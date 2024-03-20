#ifndef ARITHMETIC_OPERATORS_HPP
#define ARITHMETIC_OPERATORS_HPP

#include "node.hpp"

class AddOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    AddOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~AddOperation(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);

        stream<<"add "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" + ";
        branches[1]->Print(stream);
    }
};

class SubOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    SubOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~SubOperation(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);

        stream<<"sub "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" - "<<std::endl;
        branches[1]->Print(stream);
    }
};

class MulOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    MulOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~MulOperation(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);

        stream<<"mul "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" * "<<std::endl;
        branches[1]->Print(stream);
    }
};

class DivOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    DivOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~DivOperation(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);

        stream<<"div "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" / "<<std::endl;
        branches[1]->Print(stream);
    }
};

class ModuloOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    ModuloOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~ModuloOperation(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);

        stream<<"rem "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<" % "<<std::endl;
        branches[1]->Print(stream);
    }
};

#endif
