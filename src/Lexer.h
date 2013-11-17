/* 
 * File:   Lexer.h
 * Author: ekow
 *
 * Created on 20 October 2013, 11:12
 */

#ifndef LEXER_H
#define	LEXER_H

#include <string>
#include <fstream>

typedef enum {
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    IDENTIFIER,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    DIM,
    AS
} Token;

class Lexer
{
private:
    void tcc(std::string);
    char currentChar;
    void getChar();
    std::string buffer;
    int bufferIndex;
    int integerValue;
    std::string identifierValue;
    
public:
    Lexer(std::string);
    virtual ~Lexer();    
    
    Token getNextToken();
    int getIntegerValue();
    std::string getIdentifierValue();
};

#endif	/* LEXER_H */

