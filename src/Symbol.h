/* 
 * File:   Symbol.h
 * Author: ekow
 *
 * Created on 25 November 2013, 20:56
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <google/dense_hash_map>

typedef enum {
    NUM_INT,
    NUM_LONG,
    NUM_SINGLE,
    NUM_DOUBLE
} NumberType;

class Symbol {
public:
    Symbol();
    Symbol(const Symbol& orig);
    virtual ~Symbol();
    void setDataType(std::string);
    void setIdentifier(std::string);
    std::string getDataType();
    std::string getIdentifier();
    void setAsNumber();
    
private:
    google::dense_hash_map<const char*, Symbol*> table;
    std::string dataType;
    NumberType numberType;
    bool isNumber;
    std::string identifier;
    Symbol * parent;
};

#endif	/* SYMBOL_H */

