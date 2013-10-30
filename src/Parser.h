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

class Parser
{
private:
    Lexer * lexer;
    Token lookahead;
    bool match(Token token);
    void getToken();
    
    // Expressions parsing
    ExpressionTree * parseTerm();
    ExpressionTree * parseFactor();
    ExpressionTree * parseAddition();
    ExpressionTree * parseSubtraction();
    ExpressionTree * parseMultiplication();
    ExpressionTree * parseDivision();
    
    void parseExpression();
    
public:
    virtual ~Parser();
    void setSource(std::string source);
    void parse();
};

#endif /* PARSER_H_ */
