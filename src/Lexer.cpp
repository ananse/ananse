#include "Lexer.h"
#include <cctype>
#include <iostream>
#include <cstdlib>

Lexer::Lexer(std::string source)
{
	buffer = source;
	bufferIndex = 0;
	getChar();
}

Lexer::~Lexer()
{

}

char Lexer::getChar()
{
	if(bufferIndex < buffer.size())
	{
		lookahead = buffer[bufferIndex++];
	}
    else
    {
        lookahead = EOF;
    }
	return lookahead;
}

Token Lexer::getNextToken()
{
	// Eat whitespace
    while(isspace(lookahead)) getChar();
    
    // Match operators
    if(lookahead == '+') return PLUS;
    if(lookahead == '-') return MINUS;

    // Match integers
    if(isdigit(lookahead))
    {
    	std::string numberString;
    	while(isdigit(lookahead))
        {    
    		numberString += lookahead;
            getChar();
    	}
        integerValue = strtoi(numberString.c_str());
        return INTEGER;
    }
}

int Lexer::getIntegerValue()
{
    return integerValue;
}

