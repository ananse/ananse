/* 
 * File:   Symbols.h
 * Author: ekow
 *
 * Created on 24 November 2013, 21:11
 */

#ifndef SYMBOLS_H
#define	SYMBOLS_H

#include <google/dense_hash_map>
#include <vector>
#include "Symbol.h"
#include "Lexer.h"

typedef enum{
    ADDED,
    EXISTS,
    OVERRIDES,
    UNDEFINED
} SymbolStatus;

typedef google::dense_hash_map<std::string, Symbol *> SymbolTable;
typedef google::dense_hash_map<std::string, Symbol *>::iterator SymbolTableIterator;
typedef google::dense_hash_map<std::string, std::string> TypesTable;

class Symbols {
public:
    Symbols();
    Symbols(const Symbols& orig);
    Symbol * insert(std::string symbol, std::string type);
    Symbol * lookup(std::string identifier);
    void addType(std::string, std::string);
    bool vaildateType(std::string);
    void enterScope(std::string scope);
    void exitScope();
    virtual ~Symbols();
    void setLexer(Lexer * lexer);
    SymbolStatus getStatus();
    void dump();
    
private:    
    std::vector<SymbolTable*> symbolTableStack;
    std::vector<std::string> scopesStack;
    SymbolTable globals;
    TypesTable types;
    Lexer * lexer;
    SymbolStatus status;
    std::string currentScope;
};

#endif	/* SYMBOLTABLE_H */

