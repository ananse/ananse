/* 
 * File:   Type.cpp
 * Author: ekow
 * 
 * Created on 07 March 2014, 12:27
 */

#include "Type.h"

Type::Type()
{
}

Type::Type(const Type& orig)
{
}

Type::~Type()
{
}

Type * Type::createPrimitiveType(int rank)
{
    Type * type = new Type();
    type->primitive = true;
    type->rank = rank;
    return type;
}

int Type::getRank()
{
    return rank;
}
