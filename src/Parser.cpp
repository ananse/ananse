#include <Parser.h>
#include <iostream>
#include <cstdlib>

void Parser::setSource(std::string source)
{
	lexer = new Lexer(source);
    getToken();
}

void Parser::getToken()
{
    lookahead = lexer->getNextToken();
    
    /*switch(lookahead)
    {
        case INTEGER:
            std::cout<<"Integer"<<std::endl;
            break;
        case PLUS:
            std::cout<<"Plus"<<std::endl;
            break;
    }*/
}

void Parser::parse()
{
	parseExpression();
}

bool Parser::match(Token token)
{
    if(lookahead == token)
    {
        return true;
    }
    else
    {
        std::cerr<<"Unexpected input"<<std::endl;
        exit(1);
    }
}

void Parser::parseExpression()
{
    if(lookahead == INTEGER)
    {
        temp = lexer->getIntegerValue();
        getToken();
        switch(lookahead)
        {
            case PLUS:
                parseAddition();
                break;
            case MINUS:
                parseSubtraction();
                break;
        }
    }
}

void Parser::parseAddition()
{
    getToken();
    if(match(INTEGER))
    {
        std::cout<<(temp + lexer->getIntegerValue())<<std::endl;
    }
}

void Parser::parseSubtraction()
{
    getToken();
    if(match(INTEGER))
    {
        std::cout<<(temp - lexer->getIntegerValue())<<std::endl;
    }
}
