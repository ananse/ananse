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

    switch(lookahead)
    {
        case INTEGER:
            std::cout<<"Integer"<<std::endl;
            break;
        case PLUS:
            std::cout<<"Plus"<<std::endl;
            break;
    }
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
    ExpressionTree *expression = parseTerm();
    ExpressionTree *opr, *right, *nextNode;

    //std::cout<<(expression->hasRight() ? "Has Right" : "Nope")<<std::endl;
    nextNode = expression->hasRight() ? expression->getRight() : expression;
    
    do{
        switch(lookahead)
        {
            case PLUS:
                opr = new ExpressionTree();
                opr->setData(NODE_BIN_OPR_ADD);
                nextNode->setLeft(opr);
                right = parseTerm();
                nextNode->setRight(right);
                nextNode = right;
                break;
                
            case MINUS:
                opr = new ExpressionTree();
                opr->setData(NODE_BIN_OPR_SUBTRACT);
                nextNode->setLeft(opr);
                right = parseTerm();
                nextNode->setRight(right);
                nextNode = right;
                break;
        }
    } while(lookahead == PLUS || lookahead == MINUS);
    
    std::cout<<generator->emitExpression(expression);
    delete expression;
}

ExpressionTree * Parser::parseTerm()
{
    ExpressionTree * term = parseFactor();
    ExpressionTree * opr, * nextNode, * right;
    
    nextNode = term;
    
    do{
        switch(lookahead)
        {
            case MULTIPLY:
                opr = new ExpressionTree();
                opr->setData(NODE_BIN_OPR_MULTIPLY);
                nextNode->setLeft(opr);
                right = parseFactor();
                nextNode->setRight(right);
                nextNode = right;
                break;
                
            case DIVIDE:
                opr = new ExpressionTree();
                opr->setData(NODE_BIN_OPR_DIVIDE);
                nextNode->setLeft(opr);
                right = parseFactor();
                nextNode->setRight(right);
                nextNode = right;
                break;
        }
        getToken();
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
