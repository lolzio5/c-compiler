#ifndef FUNCTION_DEFINITION_HPP
#define FUNCTION_DEFINITION_HPP

#include "node.hpp"

class FunctionDefinition : public Node
{
private:
    Node *declaration_specifiers_;
    Node *declarator_;
    Node *compound_statement_;

public:
    FunctionDefinition(Node *declaration_specifiers, Node *declarator, Node *compound_statement) : declaration_specifiers_(declaration_specifiers), declarator_(declarator), compound_statement_(compound_statement){};
    ~FunctionDefinition()
    {
        delete declaration_specifiers_;
        delete declarator_;
        delete compound_statement_;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        stream << ".text" << std::endl;
        stream << ".globl f"<< std::endl;

        declarator_->EmitRISC(stream, context, destReg);

        if (compound_statement_ != nullptr){
            compound_statement_->EmitRISC(stream, context, destReg);
        }
    }
    void Print(std::ostream &stream) const {
        declaration_specifiers_->Print(stream);
        stream << " ";
        declarator_->Print(stream);
        stream << "() {" << std::endl;
        if (compound_statement_ != nullptr){
            compound_statement_->Print(stream);
        }
        stream << "}" << std::endl;
    }
};

class FunctionWithParamDefinition : public Node
{
private:
    Node *declarator;
    Node *parameters;

public:
    FunctionWithParamDefinition(Node *declarator_, Node *parameters_) : declarator(declarator_), parameters(parameters_){
        branches.push_back(declarator);
        branches.push_back(parameters);

    };
    ~FunctionWithParamDefinition()
    {
        for (auto branch : branches){
            delete branch;
        }
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        branches[0]->EmitRISC(stream, context, destReg);
        stream << ":" << std::endl;
        branches[1]->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        stream<<"(";
        branches[1]->Print(stream);
        stream<<")";
    }
};

class ParameterList : public Node
{
private:
    Node *parameter_list;
    Node *parameter_declaration;

public:
    ParameterList(Node *parameter_list_, Node *parameter_declaration_) : parameter_list(parameter_list_), parameter_declaration(parameter_declaration_){
        branches.push_back(parameter_list);
        branches.push_back(parameter_declaration);
    };
    ~ParameterList()
    {
        for (auto node : branches){
            delete node;
        }
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {

        branches[0]->EmitRISC(stream, context, destReg);
        branches[1]->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        branches[1]->Print(stream);
    }
};

class ParameterDeclarator : public Node
{
private:
    Node *parameter_list;
    Node *parameter_declaration;

public:
    ParameterDeclarator(Node *parameter_list_, Node *parameter_declaration_) : parameter_list(parameter_list_), parameter_declaration(parameter_declaration_){
        branches.push_back(parameter_list);
        branches.push_back(parameter_declaration);
    };
    ~ParameterDeclarator()
    {
        for (auto node : branches){
            delete node;
        }
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {

        branches[0]->EmitRISC(stream, context, destReg);
        branches[1]->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        branches[0]->Print(stream);
        branches[1]->Print(stream);
    }
};

#endif
