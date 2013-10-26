/* 
 * File:   ExpressionTree.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 14:12
 */

#include "ExpressionTree.h"
#include <cstdlib>

ExpressionTree::ExpressionTree() {
    left = NULL;
    right = NULL;
    data = NULL;
}

ExpressionTree::~ExpressionTree() {
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

