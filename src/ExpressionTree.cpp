/* 
 * File:   ExpressionTree.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 14:12
 */

#include "ExpressionTree.h"
#include <cstdlib>
#include <iostream>

ExpressionTree::ExpressionTree() 
{
    left = NULL;
    right = NULL;
    data = NULL;
}

ExpressionTree::~ExpressionTree() 
{
    if(left != NULL) delete left;
    if(right != NULL) delete right;
    if(data != NULL) free(data);
}

void ExpressionTree::setData(int integer)
{
    int * integerData = new int;
    *integerData = integer;
    data = integerData;
    type = NODE_INTEGER;
}

void ExpressionTree::setData(NodeType nodeType)
{
    type = nodeType;
}

void ExpressionTree::setLeft(ExpressionTree * node)
{
    left = node;
}

void ExpressionTree::setRight(ExpressionTree * node)
{
    right = node;
}

NodeType ExpressionTree::getType()
{
    return type;
}

ExpressionTree * ExpressionTree::getLeft()
{
    return left;
}

ExpressionTree * ExpressionTree::getRight()
{
    return right;
}

bool ExpressionTree::hasLeft()
{
    return left != NULL;
}

bool ExpressionTree::hasRight()
{
    return right != NULL;
}

void * ExpressionTree::getData()
{
    return data;
}

