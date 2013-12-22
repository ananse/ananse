/* 
 * File:   CppGenerator.h
 * Author: ekow
 *
 * Created on 26 October 2013, 15:16
 */

#ifndef CPPGENERATOR_H
#define	CPPGENERATOR_H

#include <string>
#include "../Generator.h"

class CppGenerator : public Generator
{
public:
    CppGenerator();
    CppGenerator(const CppGenerator& orig);
    virtual std::string emitDeclaration(std::string identifier, std::string datatype);
    virtual ~CppGenerator();
private:

};

#endif	/* CPPGENERATOR_H */

