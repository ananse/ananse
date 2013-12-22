/* 
 * File:   CppGenerator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:16
 */

#include "CppGenerator.h"

CppGenerator::CppGenerator() 
{
    
}

CppGenerator::CppGenerator(const CppGenerator& orig) 
{
    
}

CppGenerator::~CppGenerator() 
{
    
}

std::string CppGenerator::emitDeclaration(std::string identifier, std::string datatype)
{
    std::string localType;
    //if(datatype == "number")
    //{
        localType = "int";
    //}
    return localType + " " + identifier;
}

