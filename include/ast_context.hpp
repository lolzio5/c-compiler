#ifndef AST_CONTEXT_HPP
#define AST_CONTEXT_HPP
#include <vector>
#include <string>
#include <map>


// An object of class Context is passed between AST nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context
{
private:
    std::map<std::string, std::vector<std::string>> context;

public:
    Context() {}

    // Create a new variable
    void insertNode(const std::string& variable_name, std::string variable_type, std::string variable_value) {
        std::vector<std::string> variable_vector;
        variable_vector.push_back(variable_type);
        variable_vector.push_back(variable_value);
        context[variable_name] = variable_vector;
    }
};

#endif
