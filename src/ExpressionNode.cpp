/* 
 * File:   ExpressionNode.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 14:12
 */

#include "ExpressionNode.h"
#include <cstdlib>
#include <iostream>

ExpressionNode::ExpressionNode() 
{
    left = NULL;
    right = NULL;
}

ExpressionNode::~ExpressionNode() 
{
    if(left != NULL) delete left;
    if(right != NULL) delete right;
}

void ExpressionNode::setIntegerValue(long integer)
{
    integerValue = integer;
    type = NODE_INTEGER;
}

void ExpressionNode::setFloatValue(double floatValue)
{
    this->floatValue = floatValue;
    type = NODE_FLOAT;
}


void ExpressionNode::setNodeType(NodeType nodeType)
{
    type = nodeType;
}

void ExpressionNode::setLeft(ExpressionNode * node)
{
    left = node;
}

void ExpressionNode::setRight(ExpressionNode * node)
{
    right = node;
}

NodeType ExpressionNode::getType()
{
    return type;
}

ExpressionNode * ExpressionNode::getLeft()
{
    return left;
}

ExpressionNode * ExpressionNode::getRight()
{
    return right;
}

bool ExpressionNode::hasLeft()
{
    return left != NULL;
}

bool ExpressionNode::hasRight()
{
    return right != NULL;
}

std::string ExpressionNode::getDataType()
{
    return dataType;
}

void ExpressionNode::setDataType(std::string dataType)
{
    this->dataType = dataType;
}

long ExpressionNode::getIntegerValue()
{
    return integerValue;
}

double ExpressionNode::getFloatValue()
{
    return floatValue;
}

void ExpressionNode::setIdentifierValue(std::string identifierValue)
{
    this->identifierValue = identifierValue;
    type = NODE_IDENTIFIER;
}

std::string ExpressionNode::getIdentifierValue()
{
    return identifierValue;
}

void ExpressionNode::setStringValue(std::string stringValue)
{
	this->stringValue = stringValue;
	type = NODE_STRING;
}

std::string ExpressionNode::getStringValue()
{
	return stringValue;
}
