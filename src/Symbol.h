/* 
 * File:   Symbol.h
 * Author: ekow
 *
 * Created on 25 November 2013, 20:56
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <google/dense_hash_map>
#include <vector>
#include "abc.h"

class Symbol {
public:
    Symbol();
    Symbol(const Symbol& orig);
    virtual ~Symbol();
    
    void setDataType(std::string);
    void setIdentifier(std::string);
    void setScope(std::string);
    void setLine(int);
    void setCallable(bool);
    void setParameterList(ParameterList);
    void setAsNumber();
    
    std::string getDataType();
    std::string getIdentifier();
    std::string getNumberType();
    bool getCallable();
    ParameterList getParameterList();
    
private:
    google::dense_hash_map<const char*, Symbol*> table;
    std::string dataType;
    bool isNumber;
    bool callable;
    std::string identifier;
    Symbol * parent;
    std::string scope;
    int line;
    ParameterList parameterList;
    
};

#endif	/* SYMBOL_H */

