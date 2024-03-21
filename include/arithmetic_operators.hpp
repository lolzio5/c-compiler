#ifndef ARITHMETIC_OPERATORS_HPP
#define ARITHMETIC_OPERATORS_HPP

#include "node.hpp"

class AddOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    AddOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~AddOperation(){
        delete leftValue;
        delete rightValue;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        leftValue->EmitRISC(stream, context, leftRegister);
        rightValue->EmitRISC(stream, context, rightRegister);

        stream<<"add "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" + ";
        rightValue->Print(stream);
    }
};

class SubOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    SubOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~SubOperation(){
        delete leftValue;
        delete rightValue;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        leftValue->EmitRISC(stream, context, leftRegister);
        rightValue->EmitRISC(stream, context, rightRegister);

        stream<<"sub "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" - "<<std::endl;
        rightValue->Print(stream);
    }
};

class MulOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    MulOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~MulOperation(){
        delete leftValue;
        delete rightValue;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        leftValue->EmitRISC(stream, context, leftRegister);
        rightValue->EmitRISC(stream, context, rightRegister);

        stream<<"mul "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" * "<<std::endl;
        rightValue->Print(stream);
    }
};

class DivOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    DivOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~DivOperation(){
        delete leftValue;
        delete rightValue;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        leftValue->EmitRISC(stream, context, leftRegister);
        rightValue->EmitRISC(stream, context, rightRegister);

        stream<<"div "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" / "<<std::endl;
        rightValue->Print(stream);
    }
};

class ModuloOperation : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    ModuloOperation(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~ModuloOperation(){
        delete leftValue;
        delete rightValue;
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        leftValue->EmitRISC(stream, context, leftRegister);
        rightValue->EmitRISC(stream, context, rightRegister);

        stream<<"rem "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(leftRegister)<<", "<<context.getRegisterName(rightRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" % "<<std::endl;
        rightValue->Print(stream);
    }
};

#endif
