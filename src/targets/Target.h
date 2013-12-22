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
    void addSource(std::string source);
    virtual void build() = 0;
protected:
    Generator * generator;
    std::vector<std::string> sources;    
};

#endif	/* TARGET_H */

