#include <Parser.h>

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
