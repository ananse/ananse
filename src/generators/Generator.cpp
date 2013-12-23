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
        case NODE_ADD: return " + ";
        case NODE_SUBTRACT: return " - ";
        case NODE_MULTIPLY: return " * ";
        case NODE_DIVIDE: return " / ";
    }
}

void Generator::emitExpression(ExpressionNode * expressionNode)
{
    std::string expression;
    char buffer[1024];
    long integerNode;
    double floatNode;
    
    switch(expressionNode->getType())
    {
        case NODE_INTEGER:
            integerNode = expressionNode->getIntegerValue();
            sprintf(buffer,"%d", integerNode);
            write(buffer);
            break;
            
        case NODE_FLOAT:
            floatNode = expressionNode->getFloatValue();
            sprintf(buffer,"%f", floatNode);
            write(buffer);
            break;
            
        case NODE_IDENTIFIER:
            write(expressionNode->getIdentifierValue());
            break;
        
        case NODE_ADD:
        case NODE_SUBTRACT:
        case NODE_DIVIDE:
        case NODE_MULTIPLY:
            write("(");
            emitExpression(expressionNode->getLeft());
            write(getExpressionNodeOperator(expressionNode));
            emitExpression(expressionNode->getRight());
            write(")");
            /*expression = "(" + (
                emitExpression(expressionNode->getLeft()) + 
                (std::string)getExpressionNodeOperator(expressionNode) +  
                emitExpression(expressionNode->getRight()) +
                ")"
            );*/
            break;
    }
}

void Generator::emitAssignment()
{
    write(" = ");
} 

void Generator::emitEndOfStatement()
{
    write(";\n");
}

void Generator::openOutput(std::string path)
{
    std::cout<<"Opening ..."<<std::endl;;
    file.open(path.c_str(), std::fstream::out);
}

void Generator::closeOutput()
{
    std::cout<<"closing ..."<<std::endl;;
    file.close();
}

void Generator::write(std::string code)
{
    file<<code;
}

