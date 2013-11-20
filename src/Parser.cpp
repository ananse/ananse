#include <Parser.h>
#include <iostream>
#include <cstdlib>
#include "generators/js/JsGenerator.h"

Parser::Parser()
{
    generator = new JsGenerator();
}

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

    /*switch (lookahead)
    {
        case INTEGER:
            std::cout << "Integer - "<<lexer->getIntegerValue()<< std::endl;
            break;
        case PLUS:
            std::cout << "Plus" << std::endl;
            break;
        case DIM:
            std::cout << "Dim" << std::endl;
            break;
        case NEW_LINE:
            std::cout << "New Line"<<std::endl;
            break;
    }*/
}

void Parser::parse()
{
    do
    {
        parseDeclaration();
        //parseExpression();
        
        getToken();
        if(lookahead == NEW_LINE) getToken();
        if(lookahead == END) break;
        
    }while(true);
}

bool Parser::match(Token token)
{
    if (lookahead == token)
    {
        return true;
    } 
    else
    {
        std::cerr << "Unexpected input" << std::endl;
        exit(1);
    }
}

void Parser::parseDeclaration()
{
    if (lookahead == DIM)
    {
        std::string identifier;
        std::string datatype;
        std::string value;
    
        do{
            getToken();
            match(IDENTIFIER);
            identifier = lexer->getIdentifierValue();
            getToken();

            switch(lookahead)
            {
                case AS:
                    getToken();
                    match(IDENTIFIER);
                    datatype = lexer->getIdentifierValue();
                    getToken();
                    break;                
            }
            
            if(lookahead == EQUALS)
            {
                getToken();
                value = generator->emitExpression(parseExpression());
            }
            
            std::cout<<generator->emitDeclaration(identifier, datatype, value)<<std::endl;
        }
        while(lookahead == COMMA);
        
    }
}

/*ExpressionNode * Parser::parseExpression()
{
    return parseExpression(false);
}*/

ExpressionNode * Parser::parseExpression()
{
    ExpressionNode *expression = parseTerm();
    ExpressionNode *left, *right;

    if (expression == NULL) return NULL;

    do
    {
        switch (lookahead)
        {
            case PLUS:
                left = expression;
                expression = new ExpressionNode();
                expression->setData(NODE_ADD);
                getToken();
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                break;

            case MINUS:
                left = expression;
                expression = new ExpressionNode();
                expression->setData(NODE_SUBTRACT);
                getToken();
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                break;
        }
    } while (lookahead == PLUS || lookahead == MINUS);

    return expression;
}

ExpressionNode * Parser::parseTerm()
{
    ExpressionNode *term = parseFactor();
    ExpressionNode *left, *right;

    do
    {
        switch (lookahead)
        {
            case MULTIPLY:
                left = term;
                term = new ExpressionNode();
                term->setData(NODE_MULTIPLY);
                getToken();
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                break;

            case DIVIDE:
                left = term;
                term = new ExpressionNode();
                term->setData(NODE_DIVIDE);
                getToken();
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                break;
        }
    } while (lookahead == MULTIPLY || lookahead == DIVIDE);

    return term;
}

ExpressionNode * Parser::parseFactor()
{
    ExpressionNode * factor = NULL;
    switch (lookahead)
    {
        case INTEGER:
            factor = new ExpressionNode();
            factor->setData(lexer->getIntegerValue());
            getToken();
            break;

        case BRACKET_OPEN:
            factor = parseExpression();
            match(BRACKET_CLOSE);
            getToken();
            break;
    }
    return factor;
}

