/* 
 * File:   SymbolTable.cpp
 * Author: ekow
 * 
 * Created on 24 November 2013, 21:11
 */

#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    table.set_empty_key("");
    types.set_empty_key("");
}

SymbolTable::SymbolTable(const SymbolTable& orig)
{
}

SymbolTable::~SymbolTable()
{
}

Symbol * SymbolTable::lookup(std::string identifier)
{
    google::dense_hash_map<std::string, Symbol *>::iterator iterator = table.find(identifier);
    if(table.end() == iterator)
    {
        return NULL;
    }
    else
    {
        return table[identifier];
    }
}

Symbol * SymbolTable::insert(std::string identifier, std::string type)
{
    google::dense_hash_map<std::string, Symbol *>::iterator iterator = table.find(identifier);
    if(table.end() == iterator)
    {
        Symbol * symbol = new Symbol();
        symbol->setDataType(type);
        symbol->setIdentifier(identifier);
        table[identifier] = symbol;
        status = ADDED;
        return symbol;
    }
    else
    {
        status = EXISTS;
        return NULL;
    }
}

void SymbolTable::setLexer(Lexer* lexer)
{
    this->lexer = lexer;
}

SymbolStatus SymbolTable::getStatus()
{
    return status;
}

void SymbolTable::addType(std::string type, std::string details)
{
    types[type] = details;
}

bool SymbolTable::vaildateType(std::string type)
{
    google::dense_hash_map<std::string, std::string>::iterator iterator = types.find(type);
    if(types.end() == iterator)
    {
        return false;
    }
    else
    {
        return true;
    }
}

