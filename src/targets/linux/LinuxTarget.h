/* 
 * File:   LinuxTarget.h
 * Author: ekow
 *
 * Created on 22 December 2013, 17:47
 */

#ifndef LINUXTARGET_H
#define	LINUXTARGET_H

#include "targets/Target.h"

class LinuxTarget : public Target
{
public:
    LinuxTarget();
    LinuxTarget(const LinuxTarget& orig);
    void addSource(std::string source);
    virtual ~LinuxTarget();
    virtual Generator * getGenerator();
    virtual void build();
private:

};

#endif	/* LINUXTARGET_H */

