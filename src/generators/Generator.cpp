/* 
 * File:   Generator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:15
 */

#include "Generator.h"
#include <iostream>
#include <cstdio>

Generator::Generator() {
}

Generator::~Generator() {
}

const char * Generator::getExpressionNodeOperator(ExpressionNode* node)
{
    switch(node->getType())
    {
        case NODE_ADD: return "+";
        case NODE_SUBTRACT: return "-";
        case NODE_MULTIPLY: return "*";
        case NODE_DIVIDE: return "/";
    }
}

std::string Generator::emitExpression(ExpressionNode * expressionNode)
{
    std::string expression;
    char buffer[1024];
    int node;
    
    switch(expressionNode->getType())
    {
        case NODE_INTEGER:
            node = *((int*)expressionNode->getData());
            sprintf(buffer,"%d", node);
            expression = (std::string) buffer;
            break;
        
        case NODE_ADD:
        case NODE_SUBTRACT:
        case NODE_DIVIDE:
        case NODE_MULTIPLY:
            expression = "(" + (
                emitExpression(expressionNode->getLeft()) + 
                (std::string)getExpressionNodeOperator(expressionNode) +  
                emitExpression(expressionNode->getRight()) +
                ")"
            );
            break;
    }
    
    return expression;
}
