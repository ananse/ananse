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
    IDENTIFIER
} Token;

class Lexer
{
private:
    char lookahead;
    char getChar();
    std::string buffer;
    int bufferIndex;
    int integerValue;
    
public:
    Lexer(std::string);
    Token getNextToken();
    int getIntegerValue();
    void match(Token);
    ~Lexer();    
};

#endif	/* LEXER_H */

