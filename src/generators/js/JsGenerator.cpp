/* 
 * File:   JsGenerator.cpp
 * Author: ekow
 * 
 * Created on 19 November 2013, 19:15
 */

#include "JsGenerator.h"

JsGenerator::JsGenerator()
{
}

JsGenerator::JsGenerator(const JsGenerator& orig)
{
    
}

JsGenerator::~JsGenerator()
{
    
}

void JsGenerator::emitDeclaration(std::string identifier, std::string datatype)
{
    write((std::string)"var " + identifier);
}

