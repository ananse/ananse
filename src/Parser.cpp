#include <Parser.h>
#include <iostream>
#include <cstdlib>

Parser::Parser()
{
    generator = new Generator();
}

Parser::~Parser()
{
    
}

void Parser::setSource(std::string source)
{
	lexer = new Lexer(source);
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
	parseExpression(true);
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

ExpressionNode * Parser::parseExpression()
{
    return parseExpression(false);
}

ExpressionNode * Parser::parseExpression(bool emit)
{
    ExpressionNode *expression = parseTerm();
    ExpressionNode *left, *right;

    do{
        switch(lookahead)
        {
            case PLUS:
                left = expression;
                expression = new ExpressionNode();
                expression->setData(NODE_ADD);
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                break;
                
            case MINUS:
                left = expression;
                expression = new ExpressionNode();
                expression->setData(NODE_SUBTRACT);
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                break;
        }
    } while(lookahead == PLUS || lookahead == MINUS);
    
    if(emit)
    {
        std::cout<<generator->emitExpression(expression);
        delete expression;
    }
    else
    {
        return expression;
    }
}

ExpressionNode * Parser::parseTerm()
{
    ExpressionNode *term = parseFactor();
    ExpressionNode *left, *right;
    
    do{
        switch(lookahead)
        {
            case MULTIPLY:
                left = term;
                term = new ExpressionNode();
                term->setData(NODE_MULTIPLY);
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                break;
                
            case DIVIDE:
                left = term;
                term = new ExpressionNode();
                term->setData(NODE_DIVIDE);
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);                break;
        }
        getToken();
    } while(lookahead == MULTIPLY || lookahead == DIVIDE);  
    
    return term;
}

ExpressionNode * Parser::parseFactor()
{
    ExpressionNode * factor;
    getToken();
    switch(lookahead) 
    {
        case INTEGER:
            factor = new ExpressionNode();
            factor->setData(lexer->getIntegerValue());
            break;
        
        case BRACKET_OPEN:
            factor = parseExpression();
            match(BRACKET_CLOSE);
            break;
    }
    
    return factor;
}

