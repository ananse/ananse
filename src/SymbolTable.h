/* 
 * File:   SymbolTable.h
 * Author: ekow
 *
 * Created on 24 November 2013, 21:11
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

#include <google/dense_hash_map>
#include "Symbol.h"
#include "Lexer.h"

typedef enum{
    ADDED,
    EXISTS,
    OVERRIDES
} SymbolStatus;

class SymbolTable {
public:
    SymbolTable();
    SymbolTable(const SymbolTable& orig);
    Symbol * insert(std::string symbol, std::string type);
    Symbol * lookup(std::string identifier);
    void addType(std::string, std::string);
    bool vaildateType(std::string);
    int exists(char * identifier);
    void enterScope(char * scope);
    void exitScope();
    virtual ~SymbolTable();
    void setLexer(Lexer * lexer);
    SymbolStatus getStatus();
private:
    google::dense_hash_map<std::string, Symbol *> table;
    google::dense_hash_map<std::string, std::string> types;
    Lexer * lexer;
    SymbolStatus status;
    
};

#endif	/* SYMBOLTABLE_H */

