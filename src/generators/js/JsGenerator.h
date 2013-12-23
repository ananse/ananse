/* 
 * File:   JsGenerator.h
 * Author: ekow
 *
 * Created on 19 November 2013, 19:15
 */

#ifndef JSGENERATOR_H
#define	JSGENERATOR_H

#include <string>
#include "../Generator.h"

class JsGenerator : public Generator{
public:
    JsGenerator();
    JsGenerator(const JsGenerator& orig);
    virtual void emitDeclaration(std::string identifier, std::string datatype);
    virtual ~JsGenerator();
private:

};

#endif	/* JSGENERATOR_H */

