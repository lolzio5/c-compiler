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

        stream<<"sub "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(rightRegister)<<", "<<context.getRegisterName(leftRegister)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" - ";
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
        stream<<" * ";
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
        stream<<" / ";
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
        stream<<" % ";
        rightValue->Print(stream);
    }
};

class LessThan : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    LessThan(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~LessThan(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        branches[1]->EmitRISC(stream, context, rightRegister);
        branches[0]->EmitRISC(stream, context, leftRegister);


        stream << "slt " <<context.getRegisterName(leftRegister)<<", " <<context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "andi "<<context.getRegisterName(destReg)<< ", " <<context.getRegisterName(leftRegister)<<", 0xff"<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " < ";
        branches[1]->Print(stream);
    }
};


class LessThanEqual : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    LessThanEqual(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~LessThanEqual(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
            int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "slt " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "xori " << context.getRegisterName(destReg) << ", " << context.getRegisterName(destReg) << ", 1" << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " <= ";
        branches[1]->Print(stream);
    }
};



class GreaterThan : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    GreaterThan(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~GreaterThan(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        branches[1]->EmitRISC(stream, context, rightRegister);
        branches[0]->EmitRISC(stream, context, leftRegister);


        stream << "slt " <<context.getRegisterName(leftRegister)<<", " <<context.getRegisterName(leftRegister) << ", " << context.getRegisterName(rightRegister) << std::endl;
        stream << "andi "<<context.getRegisterName(destReg)<< ", " <<context.getRegisterName(leftRegister)<<", 0xff"<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " > ";
        branches[1]->Print(stream);
    }
};


class GreaterThanEqual : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    GreaterThanEqual(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~GreaterThanEqual(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
            int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "sgt " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "xori " << context.getRegisterName(destReg) << ", " << context.getRegisterName(destReg) << ", 1" << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " >= ";
        branches[1]->Print(stream);
    }
};

class BitwiseAnd : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    BitwiseAnd(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~BitwiseAnd(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "and " << context.getRegisterName(destReg) << ", " << context.getRegisterName(leftRegister) << ", " << context.getRegisterName(rightRegister) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " & ";
        branches[1]->Print(stream);
    }
};

class BitwiseOr : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    BitwiseOr(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~BitwiseOr(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "or " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " | ";
        branches[1]->Print(stream);
    }
};

class Equal : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    Equal(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~Equal(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();

        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "sub " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "seqz " << context.getRegisterName(destReg) << ", " << context.getRegisterName(destReg) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " == ";
        branches[1]->Print(stream);
    }
};


#endif
