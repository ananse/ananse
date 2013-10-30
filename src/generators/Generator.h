/* 
 * File:   Generator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:15
 */

#ifndef GENERATOR_H
#define	GENERATOR_H

#include "ExpressionTree.h"

class Generator {
public:
    Generator();
    Generator(const Generator& orig);
    virtual void emitExpression(ExpressionTree *);
    virtual ~Generator();
private:

};

#endif	/* GENERATOR_H */

