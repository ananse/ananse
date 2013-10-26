#include <Parser.h>
#include <iostream>
#include <cstdlib>

#include "ExpressionTree.h"

Parser::~Parser()
{
    
}

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
    ExpressionTree * expression = new ExpressionTree();
    
    if(lookahead == INTEGER)
    {
        expression->setData(lexer->getIntegerValue());
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
    
    delete expression;
}

void Parser::parseAddition()
{
    getToken();
    if(match(INTEGER))
    {
        
    }
}

void Parser::parseSubtraction()
{
    getToken();
    if(match(INTEGER))
    {
        
    }
}
