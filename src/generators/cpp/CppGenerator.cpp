/* 
 * File:   CppGenerator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:16
 */

#include "CppGenerator.h"
#include <iostream>

CppGenerator::CppGenerator() 
{
    
}

CppGenerator::CppGenerator(const CppGenerator& orig) 
{
    
}

CppGenerator::~CppGenerator() 
{
    
}

void CppGenerator::emitDeclaration(std::string identifier, std::string datatype)
{
    std::string localType;
    if(datatype == "number" || datatype == "")
    {
        localType = "int";
    }
    write(localType + " " + identifier);
}

