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
    data = NULL;
}

ExpressionNode::~ExpressionNode() 
{
    if(left != NULL) delete left;
    if(right != NULL) delete right;
    if(data != NULL) free(data);
}

void ExpressionNode::setData(int integer)
{
    int * integerData = new int;
    *integerData = integer;
    data = integerData;
    type = NODE_INTEGER;
}

void ExpressionNode::setData(NodeType nodeType)
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

void * ExpressionNode::getData()
{
    return data;
}

std::string ExpressionNode::getDataType()
{
    return dataType;
}

void ExpressionNode::setDataType(std::string dataType)
{
    this->dataType = dataType;
}
