/* 
 * File:   LinuxTarget.cpp
 * Author: ekow
 * 
 * Created on 22 December 2013, 17:47
 */

#include "LinuxTarget.h"
#include "generators/cpp/CppGenerator.h"
#include <cstdlib>

LinuxTarget::LinuxTarget()
{
    
}

LinuxTarget::LinuxTarget(const LinuxTarget& orig)
{
}

LinuxTarget::~LinuxTarget()
{
    
}

void LinuxTarget::build()
{
    std::string linkString = "";
    
    for(std::vector<std::string>::iterator i = outputSources.begin(); i != outputSources.end(); i++)
    {
        linkString += (*i) + ".o ";
        system(("g++ -std=c++11 " + (*i) + " -o " + (*i) + ".o -c" ).c_str());
    }
    
    system(("g++ -o program " + linkString).c_str());
}

Generator * LinuxTarget::getGenerator()
{
    return new CppGenerator();
}
