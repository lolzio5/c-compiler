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
        stream << ".global f"<< std::endl;

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
    FunctionWithParamDefinition(Node *declarator_, Node *parameters_) : declarator(declarator_), parameters(parameters_){}
    ~FunctionWithParamDefinition()
    {
        delete declarator;
        delete parameters;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        declarator->EmitRISC(stream, context, destReg);
        stream << ":" << std::endl;
        parameters->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        declarator->Print(stream);
        stream<<"(";
        parameters->Print(stream);
        stream<<")";
    }
};

class ParameterList : public Node
{
private:
    Node *parameter_list;
    Node *parameter_declaration;

public:
    ParameterList(Node *parameter_list_, Node *parameter_declaration_) : parameter_list(parameter_list_), parameter_declaration(parameter_declaration_){}
    ~ParameterList()
    {
        delete parameter_list;
        delete parameter_declaration;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {

        parameter_declaration->EmitRISC(stream, context, destReg);
        parameter_list->EmitRISC(stream, context, destReg);
    }
    void Print(std::ostream &stream) const {
        parameter_declaration->Print(stream);
        stream<<", ";
        parameter_list->Print(stream);
    }
};

class ParameterDeclarator : public Node
{
private:
    Node *declaration_specifier;
    Node *declarator;

public:
    ParameterDeclarator(Node *declaration_specifier_, Node *declarator_) : declaration_specifier(declaration_specifier_), declarator(declarator_){}
    ~ParameterDeclarator()
    {
        delete declaration_specifier;
        delete declarator;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {

        std::string variableName = declarator->GetIdentifier();
        int variableAddress = context.bindVariable(variableName);
        int parameterRegister = context.findFreeParamRegister();
        stream<<"sw "<<context.getRegisterName(parameterRegister)<<", "<<variableAddress<<"(s0)"<<std::endl;
    }
    void Print(std::ostream &stream) const {
        declaration_specifier->Print(stream);
        stream<<" ";
        declarator->Print(stream);
    }
};

#endif
