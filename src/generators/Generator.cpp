/* 
 * File:   Generator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:15
 */

#include "Generator.h"

Generator::Generator() {
}

Generator::~Generator() {
}

void Generator::emitExpression(ExpressionTree * expression)
{
    switch(expression->getType())
    {
        case NODE_INTEGER:
            break;
    }
}
