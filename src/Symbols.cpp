/* 
 * File:   Symbols.cpp
 * Author: ekow
 * 
 * Created on 24 November 2013, 21:11
 */

#include "Symbols.h"
#include <iostream>

Symbols::Symbols()
{
    types.set_empty_key("");
}

Symbols::Symbols(const Symbols& orig)
{
}

Symbols::~Symbols()
{
}

void Symbols::enterScope(std::string scope)
{
    SymbolTable * table = new SymbolTable();
    char lineNumber[8];
    sprintf(lineNumber, "%d", this->lexer->getLine());

    table->set_empty_key("");
    symbolTableStack.push_back(table);
    scopesStack.push_back(
            this->lexer->getSourceFile() +
            ":" +
            (std::string) lineNumber +
            ":" + scope);
    currentScope = scope;
}

void Symbols::exitScope()
{
    symbolTableStack.pop_back();
    scopesStack.pop_back();
}

Symbol * Symbols::lookup(std::string identifier)
{
    Symbol * symbol = NULL;

    // Initialize the status as UNDEFINED
    status = UNDEFINED;

    //
    for (int i = scopesStack.size() - 1; i >= 0; i--)
    {
        SymbolTable * table = symbolTableStack[i];
        std::string scope = scopesStack[i];
        SymbolTableIterator iterator = table->find(identifier);
        if (table->end() == iterator)
        {
            continue;
        }
        else
        {
            symbol = (*table)[identifier];
            if (scope == currentScope)
                status = EXISTS;
            else
                status = OVERRIDES;
        }
    }

    return symbol;
}

Symbol * Symbols::insert(std::string identifier, std::string type)
{
    Symbol * symbol = lookup(identifier);

    if (symbol == NULL || status == OVERRIDES)
    {
        SymbolTable * table = symbolTableStack.back();
        Symbol * symbol = new Symbol();
        symbol->setDataType(type);
        symbol->setIdentifier(identifier);
        symbol->setScope(currentScope);
        symbol->setLine(lexer->getLine());
        (*table)[identifier] = symbol;

        if (status == UNDEFINED) status = ADDED;

        return symbol;
    }
    else
    {
        status = EXISTS;
        return NULL;
    }
}

void Symbols::setLexer(Lexer* lexer)
{
    this->lexer = lexer;
}

SymbolStatus Symbols::getStatus()
{
    return status;
}

void Symbols::addType(std::string type, std::string details)
{
    types[type] = details;
}

bool Symbols::vaildateType(std::string type)
{
    google::dense_hash_map<std::string, std::string>::iterator iterator = types.find(type);
    if (types.end() == iterator)
    {
        return false;
    }
    else
    {
        return true;
    }
}



