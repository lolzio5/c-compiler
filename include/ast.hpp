#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "direct_declarator.hpp"
#include "function_definition.hpp"
#include "identifier.hpp"
#include "jump_statement.hpp"
#include "node.hpp"
#include "type_specifier.hpp"
#include "constant.hpp"
#include "context.hpp"
#include "variable_declarator.hpp"
#include "arithmetic_operators.hpp"
#include "control_flow.hpp"
#include "multi_declaration.hpp"
#include "function_caller.hpp"

extern Node *ParseAST(std::string file_name);

#endif
