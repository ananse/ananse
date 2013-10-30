#include <cctype>
#include <iostream>
#include <cstdlib>

#include "Lexer.h"

void Lexer::tcc(std::string prefix)
{
    std::cout<<prefix<<": '"<<currentChar<<"' val :"<<(int)currentChar<<(currentChar == EOF ? " EOF" : "")<<" buffer: "<<bufferIndex<<std::endl;
}

Lexer::Lexer(std::string source)
{
    buffer = source;
	bufferIndex = 0;
    getChar();
}

Lexer::~Lexer()
{

}

void Lexer::getChar()
{
	if(bufferIndex < buffer.size())
	{
        currentChar = buffer[bufferIndex++];
	}
    else
    {
        currentChar = EOF;
    }
}

Token Lexer::getNextToken()
{
	// Eat whitespace        
    while(isspace(currentChar))
    {
        getChar();
    }

    // Match operators
    if(currentChar == '+') { getChar(); return PLUS; }
    if(currentChar == '-') { getChar(); return MINUS; }
    if(currentChar == '*') { getChar(); return MULTIPLY; }
    if(currentChar == '/') { getChar(); return DIVIDE; }    

    // Match integers
    if(isdigit(currentChar))
    {
    	std::string numberString;
    	do
        {
    		numberString += currentChar;
            getChar();
    	}while(isdigit(currentChar));
        
        integerValue = strtol(numberString.c_str(), NULL, 10);
        return INTEGER;
    }
}

int Lexer::getIntegerValue()
{
    return integerValue;
}

