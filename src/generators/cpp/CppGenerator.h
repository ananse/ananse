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
    CppGenerator(const CppGenerator& orig);
    virtual void emitDeclaration(std::string identifier, std::string datatype);    
    virtual void emitModuleHeader();
    virtual void emitModuleFooter();
    virtual void emitEndOfStatement();
    virtual void emitPrint();
    virtual std::string openOutput(std::string source);
    virtual void closeOutput();
    virtual ~CppGenerator();
protected:
    virtual std::string getOutputFile(std::string output);
private:
    std::string outputFile;
    std::vector<std::string> headers;
    std::stringstream includes;
    std::stringstream moduleGlobals;
    std::stringstream body;
};

#endif	/* CPPGENERATOR_H */

