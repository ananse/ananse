/* 
 * File:   Generator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:15
 */

#ifndef GENERATOR_H
#define	GENERATOR_H

#include "ExpressionNode.h"
#include <string>

class Generator {
public:
    Generator();
    Generator(const Generator& orig);
    virtual std::string emitExpression(ExpressionNode *);
    virtual std::string emitDeclaration(std::string identifier, std::string datatype, std::string value) = 0;
    virtual ~Generator();
private:
    const char * getExpressionNodeOperator(ExpressionNode *);
};

#endif	/* GENERATOR_H */

