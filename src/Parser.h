/*
 * Parser.h
 *
 *  Created on: 25 Oct 2013
 *      Author: ekow
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "Lexer.h"
#include "ExpressionTree.h"
#include "generators/Generator.h"

class Parser
{
private:
    Lexer * lexer;
    Token lookahead;
    bool match(Token token);
    void getToken();
    Generator * generator;
    
    // Expressions parsing
    ExpressionTree * parseTerm();
    ExpressionTree * parseFactor();
    ExpressionTree * parseAddition();
    ExpressionTree * parseSubtraction();
    ExpressionTree * parseMultiplication();
    ExpressionTree * parseDivision();
    
    void parseExpression();
    
public:
    Parser();
    virtual ~Parser();
    void setSource(std::string source);
    void parse();
};

#endif /* PARSER_H_ */
