/* 
 * File:   Generator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:15
 */

#ifndef GENERATOR_H
#define	GENERATOR_H

#include <string>
#include <fstream>
#include <vector>

#include "CaseExpression.h"
#include "ExpressionNode.h"

/**
 * The base abstract class for the code generators. Other high level code
 * generators extend this class to help implement the translation of Ananse
 * Basic to their targets.
 */
class Generator {
public:
	/**
	 * Constructor
	 */
    Generator();

    /**
     * Copy constructor
     */
    Generator(const Generator& orig);

    /**
     * Emit an expression. Expressions are stored in a tree made up of 
     * ExpressionNode objects.
     */
    virtual void emitExpression(ExpressionNode *);
    virtual void emitDeclaration(Parameter) = 0;
    virtual void emitAssignment();
    virtual void emitEndOfStatement();
    virtual void emitModuleHeader();
    virtual void emitModuleFooter();
    virtual void emitPrint() = 0;
    virtual void emitIf(ExpressionNode * node) = 0;
    virtual void emitElseIf(ExpressionNode * node) = 0;
    virtual void emitElse() = 0;    
    virtual void emitSelect(ExpressionNode * node) = 0;
    virtual void emitCase(std::vector<CaseExpression*>) = 0;
    virtual void emitCaseElse() = 0;
    virtual void emitEndSelect() = 0;
    virtual void emitExitSelect() = 0;
    virtual void emitBeginCodeBlock() = 0;
    virtual void emitEndCodeBlock() = 0;
    virtual void emitEndProgramme() = 0;
    virtual void emitFor(std::string, ExpressionNode*, ExpressionNode*, ExpressionNode*) = 0;
    virtual void emitExitFor() = 0;
    virtual void emitContinueFor() = 0;
    virtual void emitWhile(ExpressionNode*) = 0;
    virtual void emitEndWhile() = 0;
    virtual void emitExitWhile() = 0;
    virtual void emitContinueWhile() = 0;
    virtual void emitDo(std::string, ExpressionNode*) = 0;
    virtual void emitLoop(std::string, ExpressionNode*) = 0;
    virtual void emitFunction(Parameter, ParameterList) = 0;
    virtual void emitCallSubFunction(std::string, ExpressionNodeList) = 0;
    virtual void emitEndFunction() = 0;
    virtual void emitExitFunction() = 0;
    virtual void emitReturn(ExpressionNode*) = 0;
    virtual void emitTypeCast(ExpressionNode*,std::string type) = 0;
    
    virtual ~Generator();
    virtual std::string openOutput(std::string path);
    virtual void closeOutput();
    void setAsMainModule(bool main);
    void write(std::string code);

protected:
    virtual std::string getOutputFile(std::string input) = 0;
    std::string getToken(Token);
    bool isMainModule;
    std::ofstream file;
    void setOutput(std::ostream * output);
    std::ostream * getOutput();

private:
    const char * getExpressionNodeOperator(ExpressionNode *);
    std::ostream * output;
};

#endif	/* GENERATOR_H */

