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

/**
 *
 */
class Generator {
public:
    Generator();
    Generator(const Generator& orig);
    virtual void emitExpression(ExpressionNode *);
    virtual void emitDeclaration(std::string identifier, std::string datatype) = 0;
    virtual void emitAssignment();
    virtual void emitEndOfStatement();
    virtual void emitModuleHeader();
    virtual void emitModuleFooter();
    virtual void emitPrint() = 0;
    virtual ~Generator();

    virtual std::string openOutput(std::string path);
    virtual void closeOutput();

    void setAsMainModule(bool main);
    void setOutput(std::ostream * output);
    void write(std::string code);
protected:
    virtual std::string getOutputFile(std::string input) = 0;
    bool isMainModule;
    std::ofstream file;
private:
    const char * getExpressionNodeOperator(ExpressionNode *);
    std::ostream * output;
};

#endif	/* GENERATOR_H */

