#include "Lexer.h"
#include <cctype>
#include <iostream>

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

    // Match integers
    if(isdigit(lookahead))
    {
    	std::string numberString;
    	while(isdigit(lookahead)){
            
    		numberString += lookahead;
            getChar();
    	}
        
        return INTEGER;
    }
}

int Lexer::getIntegerValue()
{
    return integerValue;
}

void Lexer::match(Token token)
{
    std::cerr<<"Unexpected input"<<std::endl;
}

