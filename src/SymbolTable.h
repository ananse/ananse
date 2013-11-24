/* 
 * File:   SymbolTable.h
 * Author: ekow
 *
 * Created on 24 November 2013, 21:11
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

#include <google/dense_hash_map>

class SymbolTable {
public:
    SymbolTable();
    SymbolTable(const SymbolTable& orig);
    virtual ~SymbolTable();
private:
    google::dense_hash_map<const char*, std::string> table;
};

#endif	/* SYMBOLTABLE_H */

