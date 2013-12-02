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

Symbol * Parser::insertSymbol(std::string identifier, std::string type)
{
    Symbol * symbol = symbolTable->insert(identifier, type);
    switch(symbolTable->getStatus())
    {
        case ADDED:
            return symbol;
        case EXISTS:
            error(identifier + " has already been declared");
    }
}

Symbol * Parser::lookupSymbol(std::string identifier)
{
    return symbolTable->lookup(identifier);
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
            
            currentSymbol = insertSymbol(identifier, datatype);
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
        ExpressionNode * expression = parseExpression();
        
        if(expression->getDataType() == currentSymbol->getDataType())
        {
            std::cout<<generator->emitExpression(expression);
        }
        else if(currentSymbol->getDataType() == "")
        {
            currentSymbol->setDataType(expression->getDataType());
            std::cout<<generator->emitExpression(expression);
        }
        else
        {
            error(
                "Cannot assign value of type " + 
                expression->getDataType() + 
                " to variable " + currentSymbol->getIdentifier() + 
                " of type " + currentSymbol->getDataType()
            );
        }
    }

}

void Parser::parseIdentifierStatements()
{
    std::string identifier;
    if(lookahead == IDENTIFIER)
    {
        identifier = lexer->getIdentifierValue();
        currentSymbol = lookupSymbol(identifier);
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
                
                if(left->getDataType() == "integer")
                {
                    if(right->getDataType() == "integer") term->setDataType("integer");
                }
                
                break;

            case DIVIDE:
                left = term;
                term = new ExpressionNode();
                term->setData(NODE_DIVIDE);
                getToken();
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                
                if(left->getDataType() == "integer")
                {
                    if(right->getDataType() == "integer") term->setDataType("integer");
                }                
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
            factor->setDataType("integer");
            getToken();
            break;
            
        case SINGLE:
            factor = new ExpressionNode();
            factor->setData(lexer->getSingleValue());
            factor->setDataType("single");
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

