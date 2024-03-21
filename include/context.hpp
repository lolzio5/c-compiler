#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <vector>
#include <string>
#include <map>

// An object of class Context is passed between AST nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context
{
private:
    std::map<std::string, int> variables; // Variabl name binding to stack location

    int usedRegisters[32] = {
        1, //x0 i = 0, reg zero
        1, //x1 i = 1, return address ra
        1,  //x2 i = 2, stack pointer sp
        1,  //x3 i = 3, global pointer gp
        1, //x4 i = 4, thread pointer tp
        0, 0, 0,  //t0-t2 i= 5-7, temporary registers
        1, 1,  //s0-s1 i = 8-9, saved registers
        0, //a0 i=10, return result
        0, 0, 0, 0, 0, 0, 0, //a1-a7 i = 11-17, argument registers
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //s2-s11 i = 18-27, saved registers
        0, 0, 0, 0, //t3-t6 i = 28-31, temporary registers
    };

    int currentStackLocation = -16;

public:
    std::map<std::string, int> getBindings(){
        return variables;
    }

    std::string NameNewBranch(){
       static int x=0;
       x++;
       return "L" + std::to_string(x);
    }

    // Add and find variables
    int bindVariable(std::string variableName){
        currentStackLocation=currentStackLocation-4;
        variables[variableName]=currentStackLocation;
        return currentStackLocation;
    }
    int variableLocation(std::string variableName){
        auto variableIndex = variables.find(variableName);
        if(variableIndex!=variables.end()){
            return variableIndex->second;
        }
        else{
            return -1;  // Return a value outside of the stack to be determined
        }
    }

    // Use or free registers
    void useRegister(int i){
        usedRegisters[i]=1;
    }
    void freeRegister(int i){
        usedRegisters[i]=0;
    }

    // Allocate registers
    int findFreeRegister(){
        for (int i=5;i<9;i++){ // Allocate to temp and saved registers
            if (usedRegisters[i]==0){
                useRegister(i);
                return i;
            }
        }
        for (int i=18;i<31;i++){ // Allocate to temp and saved registers
            if (usedRegisters[i]==0){
                useRegister(i);
                return i;
            }
        }
        return -1; // No free register found
    }
    int findFreeParamRegister(){
        for (int i=10;i<17;i++){ // Allocate to parameter registers
            if (usedRegisters[i]==0){
                useRegister(i);
                return i;
            }
        }
        return -1;
    }

    // Get Register Name for RISC-V
    std::string getRegisterName(int i){
        if((i>4)&&(i<8)){
            return 't'+std::to_string(i-5);
        }
        else if((i>9)&&(i<18)){
            return 'a'+std::to_string(i-10);
        }
        else if((i>27)&&(i<32)){
            return 't'+std::to_string(i-25);
        }
        else{
            return "x0";
        }
    }
};
# endif
