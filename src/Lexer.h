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
    NEW_LINE,
    END,
    INTEGER,
    SINGLE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUALS,
    COMMA,
    IDENTIFIER,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    DIM,
    AS,
    PERCENT,
    AMPERSAND,
    EXCLAMATION,
    HASH,
    DOLLAR,
    UNKNOWN
} Token;

class Lexer
{
private:
    void tcc(std::string);
    char currentChar;
    void getChar();
    std::string buffer;
    std::ifstream sourceStream;
    std::string sourceFile;
    int bufferIndex;
    long int integerValue;
    double singleValue;
    std::string identifierValue;
    std::string tokenString;
    long line;
    long column;
    
public:
    Lexer(std::string);
    virtual ~Lexer();    
    
    Token getNextToken();
    long getIntegerValue();
    double getSingleValue();
    std::string getIdentifierValue();
    static std::string describeToken(Token);
    std::string getTokenString();
    std::string getSourceFile();
    long getLine();
    long getColumn();
};

#endif	/* LEXER_H */

