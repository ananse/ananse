/* 
 * File:   SymbolTable.cpp
 * Author: ekow
 * 
 * Created on 24 November 2013, 21:11
 */

#include "SymbolTable.h"
#include <iostream>

SymbolTable::SymbolTable()
{
    table.set_empty_key("");
}

SymbolTable::SymbolTable(const SymbolTable& orig)
{
}

SymbolTable::~SymbolTable()
{
}

SymbolStatus SymbolTable::insert(std::string identifier, std::string type)
{
    google::dense_hash_map<std::string, Symbol *>::iterator iterator = table.find(identifier);
    if(table.end() == iterator)
    {
        table[identifier] = new Symbol();
        return ADDED;
    }
    else
    {
        return EXISTS;
    }
}

void SymbolTable::setLexer(Lexer* lexer)
{
    this->lexer = lexer;
}

