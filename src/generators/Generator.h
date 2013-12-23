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
#include <fstream>

class Generator {
public:
    Generator();
    Generator(const Generator& orig);
    virtual void emitExpression(ExpressionNode *);
    virtual void emitDeclaration(std::string identifier, std::string datatype) = 0;
    virtual void emitAssignment();
    virtual void emitEndOfStatement();
    virtual ~Generator();
    void openOutput(std::string path);
    void write(std::string code);
    void closeOutput();
private:
    const char * getExpressionNodeOperator(ExpressionNode *);
    std::ofstream file;
};

#endif	/* GENERATOR_H */

