/* 
 * File:   Symbol.h
 * Author: ekow
 *
 * Created on 25 November 2013, 20:56
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <google/dense_hash_map>

class Symbol {
public:
    Symbol();
    Symbol(const Symbol& orig);
    virtual ~Symbol();
    void setDataType(std::string);
    void setIdentifier(std::string);
    void setScope(std::string);
    void setLine(int);
    std::string getDataType();
    std::string getIdentifier();
    std::string getNumberType();
    void setAsNumber();
    
private:
    google::dense_hash_map<const char*, Symbol*> table;
    std::string dataType;
    bool isNumber;
    std::string identifier;
    Symbol * parent;
    std::string scope;
    int line;
};

#endif	/* SYMBOL_H */

