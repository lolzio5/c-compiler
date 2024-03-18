#ifndef AST_VARIABLE_DECLARATOR_HPP
#define AST_VARIABLE_DECLARATOR_HPP

#include "ast_node.hpp"
#include "ast_context.hpp"

class VariableDeclarator : public Node
{
private:
    Node *variable_name;
    Node *variable_type;
    Node *variable_value;
public:
    VariableDeclarator(Node* variable_name_, std::string variable_type_, std::string variable_value_) : variable_name(variable_name_), variable_type(variable_type_), variable_value(variable_value_){
    }

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

class VariableIdentifier : public Node
{
private:
    std::string variable_name;
public:
    VariableIdentifier(std::string *variable_name_) : variable_name(*variable_name_){}

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

#endif
