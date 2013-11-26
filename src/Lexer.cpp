
#include <cctype>
#include <iostream>
#include <cstdlib>
#include "Lexer.h"
#include "LexerException.h"

void Lexer::tcc(std::string prefix)
{
    std::cout<<prefix<<": '"<<currentChar<<"' val :"<<(int)currentChar<<(currentChar == EOF ? " EOF" : "")<<" buffer: "<<bufferIndex<<" of "<<buffer.size()<<std::endl;
}

Lexer::Lexer(std::string sourceFile)
{
    sourceStream.open(sourceFile.c_str());
    
    if(!sourceStream.is_open())
    {
        throw new LexerException();
    }
    
    this->sourceFile = sourceFile;
    line = 1;
    column = 0;
    getChar();
}

Lexer::~Lexer()
{

}

void Lexer::getChar()
{
    if(sourceStream.good())
    {
        currentChar = sourceStream.get();
        column++;
    }
    else
    {
        currentChar = EOF;      
    }
}

Token Lexer::getNextToken()
{
	// Eat whitespace    
    tokenString = "";
    while(isspace(currentChar) && currentChar != '\n' && currentChar != EOF)
    {
        getChar();
    }
    
    if(currentChar == '\n') 
    { 
        line++;
        column = 0;
        getChar(); 
        return NEW_LINE; 
    }
    
    // Match operators
    if(currentChar == '+' ) { getChar(); return PLUS; }
    if(currentChar == '-' ) { getChar(); return MINUS; }
    if(currentChar == '*' ) { getChar(); return MULTIPLY; }
    if(currentChar == '/' ) { getChar(); return DIVIDE; }    
    if(currentChar == '(' ) { getChar(); return BRACKET_OPEN; }    
    if(currentChar == ')' ) { getChar(); return BRACKET_CLOSE; }    
    if(currentChar == '=')  { getChar(); return EQUALS; }
    if(currentChar == ',')  { getChar(); return COMMA; }
    if(currentChar == '%')  { getChar(); return PERCENT; }
    if(currentChar == '&')  { getChar(); return AMPERSAND; }
    if(currentChar == '!')  { getChar(); return EXCLAMATION; }
    if(currentChar == '#')  { getChar(); return HASH; }
    if(currentChar == '$')  { getChar(); return DOLLAR; }
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
        tokenString = numberString;
        return INTEGER;
    }
    
    // Match identifiers and keywords
    if(isalpha(currentChar))
    {
        std::string identString;
        do
        {
            identString += tolower(currentChar);
            getChar();
        }while(isalnum(currentChar));
        
        identifierValue = identString;
        tokenString = identString;
        if (identString == "dim") return DIM;
        else if (identString == "as")  return AS;
        else return IDENTIFIER;
    }
    
    // Return an unknown token for whatever else is there
    tokenString = currentChar;
    return UNKNOWN;
}

int Lexer::getIntegerValue()
{
    return integerValue;
}

std::string Lexer::getIdentifierValue()
{
    return identifierValue;
}

std::string Lexer::getTokenString()
{
    return tokenString;
}

std::string Lexer::describeToken(Token token)
{
    switch (token)
    {
        case NEW_LINE:
            return "new line";
            break;
            
        case END:
            return "end of file";
            break;
            
        case INTEGER:
            return "integer";
            break;
            
        case PLUS:
            return "plus";
            break;
            
        case MINUS:
            return "minus";
            break;
    
        case MULTIPLY:
            return "multiply";
            break;
    
        case DIVIDE:
            return "divide";
            break;
            
        case EQUALS:
            return "equals";
            break;
            
        case COMMA:
            return "comma";
            break;
            
        case IDENTIFIER:
            return "identifier";
            break;
            
        case BRACKET_OPEN:
            return "bracket open";
            break;
            
        case BRACKET_CLOSE:
            return "bracket close";
            break;
    
        case DIM:
            return "dim";
            break;
    
        case AS:
            return "as";
            break;
    
        case PERCENT:
            return "percent";
            break;
            
        case AMPERSAND:
            return "ampersand";
            break;
            
        case UNKNOWN:
            return "unknown";
            break;
    }    
}

std::string Lexer::getSourceFile()
{
    return sourceFile;
}

long Lexer::getColumn()
{
    return column;
}

long Lexer::getLine()
{
    return line;
}
