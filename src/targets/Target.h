/* 
 * File:   Target.h
 * Author: ekow
 *
 * Created on 22 December 2013, 18:15
 */

#ifndef TARGET_H
#define	TARGET_H

#include <vector>
#include "generators/Generator.h"

class Target {
public:
    Target();
    Target(const Target& orig);
    virtual ~Target();
    void addSource(std::string source, bool main);
    virtual void build() = 0;
    virtual Generator * getGenerator() = 0;
protected:
    std::vector<std::string> inputSources;    
    std::vector<std::string> outputSources;
};

#endif	/* TARGET_H */

