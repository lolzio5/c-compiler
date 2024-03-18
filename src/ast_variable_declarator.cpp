#include "ast_variable_declarator.hpp"
#include "ast_context.hpp"


void VariableDeclarator::EmitRISC(std::ostream &stream, Context &context) const
{
    stream<<"li a5,"<< variable_value <<std::endl;
    stream<<"sw a5,"<< "s0" <<std::endl;

}

void VariableDeclarator::Print(std::ostream &stream) const
{
    if(variable_value.empty()){
        stream << variable_type << " " << variable_name << ";" << std::endl;
    }
    else{
        stream << variable_type << " " << variable_name << " = " << variable_value <<";" << std::endl;
    }

}

void VariableIdentifier::EmitRISC(std::ostream &stream, Context &context) const{}

void VariableIdentifier::Print(std::ostream &stream) const{}
