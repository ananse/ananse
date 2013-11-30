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
    std::string getDataType();
    std::string getIdentifier();
private:
    google::dense_hash_map<const char*, Symbol*> table;
    std::string dataType;
    std::string identifier;
    Symbol * parent;
};

#endif	/* SYMBOL_H */
