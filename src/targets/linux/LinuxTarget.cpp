/* 
 * File:   LinuxTarget.cpp
 * Author: ekow
 * 
 * Created on 22 December 2013, 17:47
 */

#include "LinuxTarget.h"
#include "generators/cpp/CppGenerator.h"

LinuxTarget::LinuxTarget()
{
    generator = new CppGenerator();
}

LinuxTarget::LinuxTarget(const LinuxTarget& orig)
{
}

LinuxTarget::~LinuxTarget()
{
}

void LinuxTarget::build()
{
    
}
