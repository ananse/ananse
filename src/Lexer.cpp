
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
    if(currentChar == EOF)  { getChar(); return END_OF_FILE; }

    // Match not equals and less than
    if(currentChar == '<')
    {
    	getChar();
    	if(currentChar == '>')
    	{
    		getChar();
    		return NOT_EQUALS;
    	}
        else if(currentChar == '=')
        {
            getChar();
            return LESS_THAN_OR_EQUALS;
        }
    	else
    	{
    		return LESS_THAN;
    	}
    }
    
    // Match greater thans
    if(currentChar == '>')
    {
        getChar();
        if(currentChar == '=')
        {
            getChar(); 
            return GREATER_THAN_OR_EQUALS;
        }
        else
        {
            return GREATER_THAN;
        }
    }

    // Match string literals
    if(currentChar == '\'' || currentChar == '"')
    {
    	char stringMarker = currentChar;
    	stringValue = "";

    	while(true)
    	{
    		getChar();
    		if(currentChar == stringMarker)
    		{
    			getChar();
    			if(currentChar != stringMarker) break;
    		}
    		stringValue += currentChar;
    	}

    	return STRING;
    }

    // Match numbers
    if(isdigit(currentChar))
    {
        bool dotSeen = false;
    	std::string numberString;
        
    	do
        {
            if(currentChar == '.')
            {
                if(dotSeen)
                    break;
                else
                    dotSeen = true; 
            }
    		numberString += currentChar;
            getChar();
    	}
        while(isdigit(currentChar) || currentChar == '.');
        
        tokenString = numberString;
        
        if(dotSeen)
        {
            singleValue = strtod(numberString.c_str(), NULL);
            return SINGLE;
        }
        else
        {
            integerValue = strtol(numberString.c_str(), NULL, 10);
            return INTEGER;
        }        
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

        if      (identString == "dim")      return DIM;
        else if (identString == "as")       return AS;
        else if (identString == "print")    return PRINT;
        else if (identString == "if")       return IF;
        else if (identString == "then")     return THEN;
        else if (identString == "else")     return ELSE;
        else if (identString == "elseif")   return ELSE_IF;
        else if (identString == "end")      return END;
        else if (identString == "exit")     return EXIT;
        else if (identString == "select")   return SELECT;
        else if (identString == "case")     return CASE;
        else if (identString == "for")      return FOR;
        else if (identString == "step")     return STEP;
        else if (identString == "next")     return NEXT;
        else if (identString == "continue") return CONTINUE;
        else if (identString == "to")       return TO;
        else if (identString == "while")    return WHILE;
        else if (identString == "wend")     return WEND;
        else if (identString == "do")       return DO;
        else if (identString == "loop")     return LOOP;
        else if (identString == "until")    return UNTIL;
        else if (identString == "function") return FUNCTION;
        else if (identString == "sub")      return SUB;
        else if (identString == "declare")  return DECLARE;
        else                                return IDENTIFIER;
    }
    
    // Return an unknown token for whatever else is there
    tokenString = currentChar;
    return UNKNOWN;
}

double Lexer::getSingleValue()
{
    return singleValue;
}

long Lexer::getIntegerValue()
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

std::string Lexer::getStringValue()
{
	return stringValue;
}

std::string Lexer::describeToken(Token token)
{
    switch (token)
    {
        case NEW_LINE:
            return "new line";
            break;
            
        case END:
            return "end";
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

        default:
        	return "unknown token";
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
