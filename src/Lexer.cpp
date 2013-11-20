
#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Lexer.h"

void Lexer::tcc(std::string prefix)
{
    std::cout<<prefix<<": '"<<currentChar<<"' val :"<<(int)currentChar<<(currentChar == EOF ? " EOF" : "")<<" buffer: "<<bufferIndex<<" of "<<buffer.size()<<std::endl;
}

Lexer::Lexer(std::string source)
{
    sourceFile.open(source.c_str());
    getChar();
}

Lexer::~Lexer()
{

}

void Lexer::getChar()
{
    if(sourceFile.good())
        currentChar = sourceFile.get();
    else
        currentChar = EOF;    
}

Token Lexer::getNextToken()
{
	// Eat whitespace        
    while(isspace(currentChar) && currentChar != '\n' && currentChar != EOF)
    {
        getChar();
    }
    
    // Match operators
    if(currentChar == '+' ) { getChar(); return PLUS; }
    if(currentChar == '-' ) { getChar(); return MINUS; }
    if(currentChar == '*' ) { getChar(); return MULTIPLY; }
    if(currentChar == '/' ) { getChar(); return DIVIDE; }    
    if(currentChar == '(' ) { getChar(); return BRACKET_OPEN; }    
    if(currentChar == ')' ) { getChar(); return BRACKET_CLOSE; }    
    if(currentChar == '\n') { getChar(); return NEW_LINE; }
    if(currentChar == '=')  { getChar(); return EQUALS; }
    if(currentChar == ',')  { getChar(); return COMMA; }
    if(currentChar == EOF) { getChar(); return END; }

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
    
    // Match identifiers and keywords
    if(isalpha(currentChar))
    {
        std::string identString;
        do
        {
            identString += currentChar;
            getChar();
        }while(isalnum(currentChar));
        
        identifierValue = identString;
        
        if (identString == "dim") return DIM;
        else if (identString == "as")  return AS;
        else return IDENTIFIER;
    }
}

int Lexer::getIntegerValue()
{
    return integerValue;
}

std::string Lexer::getIdentifierValue()
{
    return identifierValue;
}
