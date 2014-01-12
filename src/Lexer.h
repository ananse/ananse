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
    END_OF_FILE,
    STRING,
    INTEGER,
    SINGLE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUALS,
    NOT_EQUALS,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUALS,
    LESS_THAN_OR_EQUALS,
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
    UNKNOWN,
    PRINT,
    IF,
    THEN,
    ELSE,
    ELSE_IF,
    SELECT,
    CASE,
    TO,
    IS
} Token;

/**
 * The full lexer
 */
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
    std::string stringValue;
    long line;
    long column;
    
public:
    Lexer(std::string);
    virtual ~Lexer();    
    
    Token getNextToken();
    static std::string describeToken(Token);
    std::string getTokenString();

    long getIntegerValue();
    double getSingleValue();
    std::string getIdentifierValue();
    std::string getStringValue();

    std::string getSourceFile();
    long getLine();
    long getColumn();
};

#endif	/* LEXER_H */

