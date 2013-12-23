/* 
 * File:   Target.cpp
 * Author: ekow
 * 
 * Created on 22 December 2013, 18:15
 */

#include "Target.h"
#include "Parser.h"

Target::Target()
{
}

Target::Target(const Target& orig)
{
}

Target::~Target()
{
}

void Target::addSource(std::string source)
{
    Parser * parser = new Parser(generator, source);
    parser->parse();
    delete parser;
}

