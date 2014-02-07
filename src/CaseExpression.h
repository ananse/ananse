/* 
 * File:   CaseExpression.h
 * Author: ekow
 *
 * Created on 12 January 2014, 18:01
 */

#ifndef CASEEXPRESSION_H
#define	CASEEXPRESSION_H

#include "ExpressionNode.h"
#include "abc.h"

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
    void setComparator(Token);
    Token getComparator();
    
private:
    ExpressionNode * primaryExpression;
    ExpressionNode * secondaryExpression;
    CaseExpressionType type;
    Token comparator;
};

#endif	/* CASEEXPRESSION_H */
