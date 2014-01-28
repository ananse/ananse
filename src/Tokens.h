/* 
 * File:   Tokens.h
 * Author: ekow
 *
 * Created on 26 January 2014, 15:31
 */

#ifndef TOKENS_H
#define	TOKENS_H

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

#endif	/* TOKENS_H */

