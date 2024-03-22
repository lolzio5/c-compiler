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
    FunctionDefinition(Node *declaration_specifiers, Node *declarator, Node *compound_statement) : declaration_specifiers_(declaration_specifiers), declarator_(declarator), compound_statement_(compound_statement){}
    ~FunctionDefinition(){
        delete declaration_specifiers_;
        delete declarator_;
        delete compound_statement_;
    }
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        if(declarator_ != nullptr){
            declarator_->EmitRISC(stream, context, destReg);
        }
        if (compound_statement_ != nullptr){
            compound_statement_->EmitRISC(stream, context, destReg);
        }
    }
    void Print(std::ostream &stream) const {
        //comment out for extra passed test case
        /*if(declaration_specifiers_!=nullptr){
            declaration_specifiers_->Print(stream);
        }
        stream << " ";
        if(declarator_!=nullptr){
            declarator_->Print(stream);
        }
        stream << "() {" << std::endl;
        if (compound_statement_ != nullptr){
            compound_statement_->Print(stream);
        }
        stream << "}" << std::endl;
        */
    }
};

class EmptyFunctionDefinition : public Node
{
private:
    Node *declarator_;
    Node *specifier_;

public:
    EmptyFunctionDefinition(Node *declarator, Node *specifier) : declarator_(declarator), specifier_(specifier){};
    ~EmptyFunctionDefinition()
    {
        delete declarator_;
        delete specifier_;
    };
    void EmitRISC(std::ostream &stream, Context &context, int destReg) const override {}
    void Print(std::ostream &stream) const {
        declarator_->Print(stream);
        stream<<" ";
        specifier_->Print(stream);
        stream<<"();"<<std::endl;
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
        std::string functionName=declarator->GetIdentifier();
        if(context.isFunctionDeclared(functionName)){
            parameters->EmitRISC(stream, context, destReg);
            context.callFunction();
            stream<<"addi sp,sp,-16"<<std::endl;
            stream<<"sw ra,12(sp)"<<std::endl;
            stream<<"sw s0,8(sp)"<<std::endl;
            stream<<"addi s0,sp,16"<<std::endl;
            stream<<"call "<<functionName<<std::endl;
        }
        else{
            context.declareFunction(functionName);
            stream << ".globl ";
            declarator->EmitRISC(stream, context, destReg);
            stream<<std::endl;
            declarator->EmitRISC(stream, context, destReg);
            stream << ":" << std::endl;
            if(parameters!=nullptr){
                parameters->EmitRISC(stream, context, destReg);
            }
        }
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

        std::string variableType = declaration_specifier->GetType();
        std::string variableName = declarator->GetIdentifier();

        int variableAddress = context.bindVariable(variableName, variableType);
        int parameterRegister = context.findFreeParamRegister();

        if(variableType=="float"){
            stream<<"fsw f"<<context.getRegisterName(parameterRegister)<<", " <<variableAddress<<"(sp)"<<std::endl;
        }
        else if (variableType=="double"){
            stream<<"fsd f"<<context.getRegisterName(parameterRegister)<<", " <<variableAddress<<"(sp)"<<std::endl;
        }
        else{
             stream<<"sw "<<context.getRegisterName(parameterRegister)<<", "<<variableAddress<<"(sp)"<<std::endl;
        }
    }
    void Print(std::ostream &stream) const {
        declaration_specifier->Print(stream);
        stream<<" ";
        declarator->Print(stream);
    }
};

#endif
