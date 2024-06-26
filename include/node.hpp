#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

#include "context.hpp"

class Node
{
protected:
    std::vector<Node *> branches;

public:
    Node(){};
    virtual ~Node(){
        for (auto branch : branches){
            delete branch;
        }
    }
    virtual void EmitRISC(std::ostream &stream, Context &context, int destReg) const = 0;
    virtual void Print(std::ostream &stream) const = 0;
    virtual std::string GetIdentifier() const {
        std::cerr<<"Identifier Error"<<std::endl;
    }
    virtual std::string GetType() const {
        std::cerr<<"Type Error"<<std::endl;
    }
    virtual int GetSize() const{
        std::cerr<<"Size Error"<<std::endl;
    }
};

class NodeList : public Node
{
private:
    std::vector<Node *> nodes;

public:
    NodeList(Node *first_node) : nodes({first_node}) {}

    ~NodeList()
    {
        for (auto node : nodes)
        {
            delete node;
        }

    }

    void PushBack(Node *item){
        nodes.push_back(item);
    }

    virtual void EmitRISC(std::ostream &stream, Context &context, int destReg) const {
        for (auto node : nodes){
            if (node == nullptr){
                continue;
            }
            node->EmitRISC(stream, context, destReg);
        }
    }

    virtual void Print(std::ostream &stream) const {
        for (auto node : nodes){
            if (node == nullptr){
                continue;
            }
            node->Print(stream);
        }
    }

    int getSize() const {
        return nodes.size();
    }
};

#endif
