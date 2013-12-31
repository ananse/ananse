/* 
 * File:   Symbol.cpp
 * Author: ekow
 * 
 * Created on 25 November 2013, 20:56
 */

#include "Symbol.h"

Symbol::Symbol()
{
}

Symbol::Symbol(const Symbol& orig)
{
}

Symbol::~Symbol()
{
}

void Symbol::setDataType(std::string type)
{
    this->dataType = type;
}

std::string Symbol::getDataType()
{
    return dataType;
}

std::string Symbol::getIdentifier()
{
    return identifier;
}

void Symbol::setIdentifier(std::string identifier)
{
    this->identifier = identifier;
}

void Symbol::setAsNumber()
{
    isNumber = true;
}

void Symbol::setScope(std::string scope)
{
    this->scope = scope;
}

void Symbol::setLine(int line)
{
    this->line = line;
}
