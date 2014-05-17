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

void Target::addMainSource(std::string source)
{
    addSource(source, true);
}

void Target::addOtherSource(std::string source)
{
    addSource(source, false);
}

void Target::addSource(std::string source, bool main)
{
    Generator * generator = getGenerator();
    inputSources.push_back(source);
    generator->setAsMainModule(main);
    outputSources.push_back(generator->openOutput(source));
    generator->emitModuleHeader();
    Parser * parser = new Parser(generator, source);
    parser->parse();
    generator->emitModuleFooter();
    generator->closeOutput();
    delete parser;
    delete generator;
}

