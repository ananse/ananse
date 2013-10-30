#include <Parser.h>
#include <iostream>
#include <cstdlib>

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
    ExpressionTree * expression = parseTerm();

    do{
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
    } while(lookahead == PLUS || lookahead == MINUS);
    
    delete expression;
}

ExpressionTree * Parser::parseTerm()
{
    ExpressionTree * term = parseFactor();
    do{
        getToken();
        switch(lookahead)
        {
            case MULTIPLY:
                parseMultiplication();
                break;
            case DIVIDE:
                parseDivision();
                break;
        }
    } while(lookahead == MULTIPLY || lookahead == DIVIDE);  
    
    return term;
}

ExpressionTree * Parser::parseFactor()
{
    ExpressionTree * factor = new ExpressionTree();
    getToken();
    if(lookahead == INTEGER) 
    {
        factor->setData(lexer->getIntegerValue());
    }
    
    return factor;
}

ExpressionTree * Parser::parseAddition()
{
    return parseTerm();
}

ExpressionTree * Parser::parseSubtraction()
{
    return parseTerm();
}

ExpressionTree * Parser::parseMultiplication()
{
    return parseFactor();
}

ExpressionTree * Parser::parseDivision()
{
    return parseFactor();
}