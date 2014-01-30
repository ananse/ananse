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
        case NODE_EQUALS: return " == ";
        case NODE_NOT_EQUALS: return " != ";
        case NODE_GREATER_THAN: return " > ";
        case NODE_LESS_THAN: return " < ";
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
    char buffer[256];
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
        case NODE_EQUALS:
        case NODE_NOT_EQUALS:
        case NODE_GREATER_THAN:
        case NODE_LESS_THAN:
            write("(");
            emitExpression(expressionNode->getLeft());
            write(getExpressionNodeOperator(expressionNode));
            emitExpression(expressionNode->getRight());
            write(")");
            break;

        case NODE_STRING:
        	write("\"");
        	write(expressionNode->getStringValue());
        	write("\"");
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

std::string Generator::getToken(Token token)
{
    switch(token)
    {
        case EQUALS: return " == ";
        case NOT_EQUALS: return "!=";
        case GREATER_THAN: return ">";
        case LESS_THAN: return "<";
        case GREATER_THAN_OR_EQUALS: return ">=";
        case LESS_THAN_OR_EQUALS: return "<=";
    }
}

