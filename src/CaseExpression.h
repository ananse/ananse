/* 
 * File:   CaseExpression.h
 * Author: ekow
 *
 * Created on 12 January 2014, 18:01
 */

#ifndef CASEEXPRESSION_H
#define	CASEEXPRESSION_H

#include "ExpressionNode.h"

typedef enum{
    CASE_EXPRESSION,
    CASE_TO,
    CASE_IS
} CaseExpressionType;

class CaseExpression {
public:
    CaseExpression(
        CaseExpressionType type, 
        ExpressionNode * primaryExpression, 
        ExpressionNode * secondaryExpression
    );
    CaseExpression(const CaseExpression& orig);
    virtual ~CaseExpression();
    ExpressionNode * getPrimaryExpression();
    ExpressionNode * getSecondaryExpression();
    CaseExpressionType getType();
    
private:
    ExpressionNode * primaryExpression;
    ExpressionNode * secondaryExpression;
    CaseExpressionType type;
};

#endif	/* CASEEXPRESSION_H */

