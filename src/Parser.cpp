#include <Parser.h>
#include <iostream>
#include <cstdlib>
#include "generators/js/JsGenerator.h"
#include "LexerException.h"

Parser::Parser()
{
    generator = new JsGenerator();
}

Parser::~Parser()
{

}

void Parser::out(std::string type, std::string message)
{
    std::cerr<<
        lexer->getSourceFile()<<":"<<lexer->getLine()<<":"<<lexer->getColumn()<<
        ": "<<type<<": "<<message<<std::endl;
}

void Parser::error(std::string message)
{
    out("error", message);
    exit(1);
}

void Parser::setSource(std::string source)
{
    try{
        lexer = new Lexer(source);
        symbolTable = new SymbolTable();
    }
    catch(LexerException * e)
    {
        std::cerr<<"Could not open file "<<source<<std::endl;
        exit(1);
    }
    getToken();
}

void Parser::getToken()
{
    lookahead = lexer->getNextToken();
}

void Parser::parse()
{
    do
    {
        parseDeclaration();
        parseIdentifierStatements();
        
        // Detect newlines or EOFs
        if(lookahead != NEW_LINE && lookahead != END)
        {
            error("Unexpected token '" + lexer->getTokenString() + "'");
        }
        
        // Get the next token
        getToken();
        
        // Detect EOFs
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
        error("Unexpected " + Lexer::describeToken(lookahead) + " '" + lexer->getTokenString() + "'. Expected " + Lexer::describeToken(token) + ".");
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
                    
                case PERCENT:
                    datatype = "integer";
                    getToken();
                    break;
                    
                case AMPERSAND:
                    datatype = "long";
                    getToken();
                    break;
                    
                case EXCLAMATION:
                    datatype = "single";
                    getToken();
                    break;
                    
                case HASH:
                    datatype = "double";
                    getToken();
                    break;
            }
            
            switch(symbolTable->insert(identifier, datatype))
            {
                case EXISTS:
                    error("Cannot redeclare variable " + identifier);
            }
            std::cout<<generator->emitDeclaration(identifier, datatype);
            parseAssignment();
            std::cout<<generator->emitEndOfStatement();                        
        }
        while(lookahead == COMMA);
    }
}

void Parser::parseAssignment()
{
    if(lookahead == EQUALS)
    {
        getToken();
        std::cout<<generator->emitAssignment();
        std::cout<<generator->emitExpression(parseExpression());
    }

}

void Parser::parseIdentifierStatements()
{
    std::string identifier;
    if(lookahead == IDENTIFIER)
    {
        identifier = lexer->getIdentifierValue();
        getToken();
        switch(lookahead)
        {
            case EQUALS:
                std::cout<<identifier;
                parseAssignment();
                std::cout<<generator->emitEndOfStatement();
                break;
        }
    }
}

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

