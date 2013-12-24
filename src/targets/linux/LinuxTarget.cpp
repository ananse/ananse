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
    system(("g++ " + outputSources[0]).c_str());
}

Generator * LinuxTarget::getGenerator()
{
    return new CppGenerator();
}
