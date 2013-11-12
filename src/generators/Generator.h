/* 
 * File:   Generator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:15
 */

#ifndef GENERATOR_H
#define	GENERATOR_H

#include "ExpressionTree.h"
#include <string>

class Generator {
public:
    Generator();
    Generator(const Generator& orig);
    virtual std::string emitExpression(ExpressionTree *);
    virtual ~Generator();
private:
    const char * getExpressionNodeOperator(ExpressionTree *);
};

#endif	/* GENERATOR_H */

