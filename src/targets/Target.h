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
    void addMainSource(std::string source);
    void addOtherSource(std::string source);
    virtual void build() = 0;
    virtual Generator * getGenerator() = 0;
protected:
    void addSource(std::string source, bool main);
    std::vector<std::string> inputSources;    
    std::vector<std::string> outputSources;
};

#endif	/* TARGET_H */

