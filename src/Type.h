/* 
 * File:   Type.h
 * Author: ekow
 *
 * Created on 07 March 2014, 12:27
 */

#ifndef TYPE_H
#define	TYPE_H

class Type {
public:
    Type();
    Type(const Type& orig);
    virtual ~Type();
    static Type * createPrimitiveType(int rank);
    int getRank();
private:
    bool primitive;
    int rank;
};

#endif	/* TYPE_H */

