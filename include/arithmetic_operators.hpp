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


class LogicalAnd : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    LogicalAnd(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~LogicalAnd(){
        delete leftValue;
        delete rightValue;
    }


    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        // Generate labels for the short-circuit evaluation
        std::string trueLabel = context.nameNewBranch();
        std::string falseLabel = context.nameNewBranch();
        std::string endLabel = context.nameNewBranch();

        // Evaluate the left operand
        leftValue->EmitRISC(stream, context, destReg);

        // If the left operand is false, short-circuit and jump to the false label
        stream << "beqz " << context.getRegisterName(destReg) << ", " << falseLabel << std::endl;

        // Evaluate the right operand if the left operand is true
        rightValue->EmitRISC(stream, context, destReg);

        // If the right operand is true, jump to the true label
        stream << "bnez " << context.getRegisterName(destReg) << ", " << trueLabel << std::endl;

        // False label: set the destination register to false
        stream << falseLabel << ":" << std::endl;
        stream << "li " << context.getRegisterName(destReg) << ", 0" << std::endl;
        stream << "j " << endLabel << std::endl;

        // True label: set the destination register to true
        stream << trueLabel << ":" << std::endl;
        stream << "li " << context.getRegisterName(destReg) << ", 1" << std::endl;

        // End label
        stream << endLabel << ":" << std::endl;
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" && ";
        rightValue->Print(stream);
    }
};

class LogicalOr : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    LogicalOr(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {}
    ~LogicalOr(){
        delete leftValue;
        delete rightValue;
    }


    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        // Generate labels for the short-circuit evaluation
        std::string trueLabel = context.nameNewBranch();
        std::string falseLabel = context.nameNewBranch();
        std::string endLabel = context.nameNewBranch();

        // Evaluate the left operand
        leftValue->EmitRISC(stream, context, destReg);

        // If the left operand is true, short-circuit and jump to the true label
        stream << "bnez " << context.getRegisterName(destReg) << ", " << trueLabel << std::endl;

        // Evaluate the right operand if the left operand is false
        rightValue->EmitRISC(stream, context, destReg);

        // If the right operand is true, jump to the true label
        stream << "bnez " << context.getRegisterName(destReg) << ", " << trueLabel << std::endl;

        // False label: set the destination register to false
        stream << falseLabel << ":" << std::endl;
        stream << "li " << context.getRegisterName(destReg) << ", 0" << std::endl;
        stream << "j " << endLabel << std::endl;

        // True label: set the destination register to true
        stream << trueLabel << ":" << std::endl;
        stream << "li " << context.getRegisterName(destReg) << ", 1" << std::endl;

        // End label
        stream << endLabel << ":" << std::endl;
    }
    void Print(std::ostream &stream) const {
        leftValue->Print(stream);
        stream<<" || ";
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

        stream<<"div "<<context.getRegisterName(destReg)<<", "<<context.getRegisterName(rightRegister)<<", "<<context.getRegisterName(leftRegister)<<std::endl;
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
        int tempreg = context.findFreeRegister();
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "slt " << context.getRegisterName(tempreg) << ", " << context.getRegisterName(leftRegister) << ", " << context.getRegisterName(rightRegister) << std::endl;
        stream << "xori " << context.getRegisterName(tempreg) << ", " << context.getRegisterName(tempreg) << ", 1" << std::endl;
        stream << "sub " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "seqz " << context.getRegisterName(destReg) << ", " << context.getRegisterName(destReg) << std::endl;
        stream << "or " << context.getRegisterName(destReg)<< ", "<< context.getRegisterName(destReg) << ", " <<context.getRegisterName(tempreg)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
        context.freeRegister(tempreg);
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
        int tempreg = context.findFreeRegister();
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "slt " << context.getRegisterName(tempreg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "xori " << context.getRegisterName(tempreg) << ", " << context.getRegisterName(tempreg) << ", 1" << std::endl;
        stream << "sub " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        stream << "seqz " << context.getRegisterName(destReg) << ", " << context.getRegisterName(destReg) << std::endl;
        stream << "or " << context.getRegisterName(destReg)<< ", "<< context.getRegisterName(destReg) << ", " <<context.getRegisterName(tempreg)<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
        context.freeRegister(tempreg);
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

class BitwiseXOR : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    BitwiseXOR(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~BitwiseXOR(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "xor " << context.getRegisterName(destReg) << ", " << context.getRegisterName(rightRegister) << ", " << context.getRegisterName(leftRegister) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " ^ ";
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



class NotEqual : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    NotEqual(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~NotEqual(){
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
        stream << "xori " << context.getRegisterName(destReg) <<", "<<context.getRegisterName(destReg)<<", 1"<<std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " != ";
        branches[1]->Print(stream);
    }
};

class ShiftLeft : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    ShiftLeft(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~ShiftLeft(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "sll " << context.getRegisterName(destReg) << ", " << context.getRegisterName(leftRegister) << ", " << context.getRegisterName(rightRegister) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " << ";
        branches[1]->Print(stream);
    }
};

class ShiftRight : public Node
{
private:
    Node* leftValue;
    Node* rightValue;
public:
    ShiftRight(Node* leftValue_, Node* rightValue_) : leftValue(leftValue_), rightValue(rightValue_) {
        branches.push_back(leftValue);
        branches.push_back(rightValue);
    }
    ~ShiftRight(){
        for (auto branch : branches){
            delete branch;
        }
    }

    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        int leftRegister = context.findFreeRegister();
        int rightRegister = context.findFreeRegister();
        
        branches[0]->EmitRISC(stream, context, leftRegister);
        branches[1]->EmitRISC(stream, context, rightRegister);
        stream << "slr " << context.getRegisterName(destReg) << ", " << context.getRegisterName(leftRegister) << ", " << context.getRegisterName(rightRegister) << std::endl;
        context.freeRegister(leftRegister);
        context.freeRegister(rightRegister);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream << " << ";
        branches[1]->Print(stream);
    }
};

#endif
