/* 
 * File:   Generator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:15
 */

#include "Generator.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

Generator::Generator() {
    
}

Generator::~Generator() {
    if(file.is_open()) file.close();    
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

void Generator::setAsMainModule(bool main)
{
    isMainModule = main;
}

void Generator::emitModuleHeader(){}
void Generator::emitModuleFooter(){}

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

std::string Generator::openOutput(std::string path)
{
	// Get the filename without the extension
	std::string outputFile = getOutputFile(path);
    file.open(outputFile.c_str());
    setOutput(&file);
    return outputFile;
}

void Generator::closeOutput()
{
	file.close();
}

void Generator::setOutput(std::ostream * output)
{
    this->output = output;
}

void Generator::write(std::string code)
{
    (*output)<<code;
}

