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

const char * Generator::getExpressionNodeOperator(ExpressionTree* node)
{
    switch(node->getType())
    {
        case NODE_BIN_OPR_ADD: return "+";
        case NODE_BIN_OPR_SUBTRACT: return "-";
        case NODE_BIN_OPR_MULTIPLY: return "*";
        case NODE_BIN_OPR_DIVIDE: return "/";
    }
}

std::string Generator::emitExpression(ExpressionTree * expressionNode)
{
    std::string expression;
    char buffer[1024];
    int node;
    
    switch(expressionNode->getType())
    {
        case NODE_INTEGER:
            node = *((int*)expressionNode->getData());
                
            if(expressionNode->hasLeft())
            {
                sprintf(buffer,"%d", node);
                expression ="(" + (
                    (std::string)buffer + 
                    (std::string)getExpressionNodeOperator(expressionNode->getLeft()) +  
                    emitExpression(expressionNode->getRight()) +
                    ")"
                );
            }
            else
            {
                sprintf(buffer,"%d", node);
                expression = (std::string) buffer;
            }
            break;
    }
    
    return expression;
}
