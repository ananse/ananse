/* 
 * File:   CppGenerator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:16
 */

#ifndef CPPGENERATOR_H
#define	CPPGENERATOR_H

#include <string>
#include <sstream>
#include <vector>
#include "../Generator.h"

typedef struct{
    int line;
    std::string identifier;
    std::string datatype;
    std::string expression;
} CppVariableDeclaration;

/**
 *
 */
class CppGenerator : public Generator
{
public:
    CppGenerator();
    //CppGenerator(const CppGenerator& orig);
    //virtual ~CppGenerator();

    virtual void emitDeclaration(std::string identifier, std::string datatype, bool global);    
    virtual void emitModuleHeader();
    virtual void emitModuleFooter();
    virtual void emitEndOfStatement();
    virtual void emitPrint();
    virtual void emitIf(ExpressionNode * condition);
    virtual void emitElseIf(ExpressionNode * condition);
    virtual void emitElse();
    virtual void emitSelect(ExpressionNode * node);
    virtual void emitCase(std::vector<CaseExpression*>);
    virtual void emitCaseElse();
    virtual void emitEndSelect();
    virtual void emitExitSelect();
    virtual void emitBeginCodeBlock();
    virtual void emitEndCodeBlock();
    virtual void emitEndProgramme();
    virtual std::string openOutput(std::string source);
    virtual void closeOutput();

protected:
    virtual std::string getOutputFile(std::string output);
    void addHeader(std::string header);
    bool indenterEnabled;
    int indent;
    std::string indentation();
    void writeCaseExpression(std::string, CaseExpression *);

private:
    std::string outputFile;
    std::vector<std::string> headers;
    std::stringstream includes;
    std::stringstream moduleGlobals;
    std::stringstream body;
    int selectCases;
    std::vector<std::string> caseVariables;
    std::string nextCodeBlockPrefix;
};

#endif	/* CPPGENERATOR_H */
