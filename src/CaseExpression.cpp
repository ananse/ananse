/* 
 * File:   CaseExpression.cpp
 * Author: ekow
 * 
 * Created on 12 January 2014, 18:01
 */

#include "CaseExpression.h"

CaseExpression::CaseExpression(
    CaseExpressionType type, 
    ExpressionNode * primaryExpression, 
    ExpressionNode * secondaryExpression
)
{
    this->type = type;
    this->primaryExpression = primaryExpression;
    this->secondaryExpression = secondaryExpression;
}

CaseExpression::CaseExpression(const CaseExpression& orig)
{
}

CaseExpression::~CaseExpression()
{
}

ExpressionNode * CaseExpression::getPrimaryExpression()
{
    return primaryExpression;
}

ExpressionNode * CaseExpression::getSecondaryExpression()
{
    return secondaryExpression;
}

CaseExpressionType CaseExpression::getType()
{
    return type;
}
