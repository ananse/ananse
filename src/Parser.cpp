#include <Parser.h>
#include <iostream>

void Parser::setSource(std::string source)
{
	lexer = new Lexer(source);
    lookahead = lexer->getNextToken();
}

void Parser::parse()
{
	parseExpression();
}

void Parser::parseExpression()
{
    if(lookahead == INTEGER)
    {
        
    }
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
        //exit(0);
    }
}
