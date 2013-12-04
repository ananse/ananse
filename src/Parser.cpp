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
    delete generator;
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
            if(type == "integer")
            {
                symbol->setAsNumber();
            }
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
        symbolTable->addType("number", "primitive");
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
                    datatype = "number";
                    getToken();
                    break;
            }
            
            if(!symbolTable->vaildateType(datatype) && datatype != "")
            {
                error("Unknown data type `" + datatype + "`");
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
        
        if(isNumeric(expression->getDataType()) && isNumeric(currentSymbol->getDataType()))
        {
            std::cout<<generator->emitExpression(expression);
        }
        else if(expression->getDataType() == currentSymbol->getDataType())
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
                expression->setNodeType(NODE_ADD);
                getToken();
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                expression->setDataType(resolveNumericTypes(left->getDataType(), right->getDataType()));
                break;

            case MINUS:
                left = expression;
                expression = new ExpressionNode();
                expression->setNodeType(NODE_SUBTRACT);
                getToken();
                right = parseTerm();
                expression->setRight(right);
                expression->setLeft(left);
                expression->setDataType(resolveNumericTypes(left->getDataType(), right->getDataType()));
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
                term->setNodeType(NODE_MULTIPLY);
                getToken();
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                term->setDataType(resolveNumericTypes(left->getDataType(), right->getDataType()));
                break;

            case DIVIDE:
                left = term;
                term = new ExpressionNode();
                term->setNodeType(NODE_DIVIDE);
                getToken();
                right = parseFactor();
                term->setRight(right);
                term->setLeft(left);
                term->setDataType(resolveNumericTypes(left->getDataType(), right->getDataType()));                
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
            factor->setIntegerValue(lexer->getIntegerValue());
            factor->setDataType("integer");
            getToken();
            break;
            
        case SINGLE:
            factor = new ExpressionNode();
            factor->setFloatValue(lexer->getSingleValue());
            factor->setDataType("single");
            getToken();
            break;
            
        case IDENTIFIER:
            factor = new ExpressionNode();
            factor->setIdentifierValue(lexer->getIdentifierValue());
            factor->setDataType(lookupSymbol(lexer->getIdentifierValue())->getDataType());
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

bool Parser::isNumeric(std::string datatype)
{
    if(datatype == "integer" || datatype == "single" || datatype == "double"  || 
       datatype == "long"    || datatype == "number")
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Parser::resolveNumericTypes(std::string left, std::string right)
{
    if(left == "integer")
    {
        if(right == "integer") return "integer";
        if(right == "single") return "single";
    }
    else if(left == "single")
    {
        if(right == "single" || right == "integer") return "single";
    }    
}
