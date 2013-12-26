#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "Lexer.h"
#include "ExpressionNode.h"
#include "generators/Generator.h"
#include "SymbolTable.h"

class Parser
{
private:

	typedef struct{
		Token tokens[4];
		NodeType nodes[4];
		int numOperators;
	} OperatorLevel;

    Lexer * lexer;
    SymbolTable * symbolTable;
    Token lookahead;
    Generator * generator;
    static OperatorLevel operators[];
    static int numOperators;
    
    bool match(Token token);
    void getToken();

    void out(std::string type, std::string message);
    void error(std::string message);
    
    Symbol * lookupSymbol(std::string identifier);
    Symbol * insertSymbol(std::string identifier, std::string type);
    Symbol * currentSymbol;
    
    // Declarations and assignments
    void parseDeclaration();
    void parseAssignment();
    void parseIdentifierStatements();
    void parsePrint();
    void parseIf();
    
    // Expressions parsing
    ExpressionNode * parseExpression();
    static ExpressionNode * parseBinaryOperators(int precedence, Parser * instance);
    static ExpressionNode * parseUnaryOperators(Parser * instance);
    
    static bool isNumeric(std::string datatype);
    std::string resolveNumericTypes(std::string left, std::string right);
    void setSource(std::string source);
    
public:
    Parser(Generator * generator, std::string source);
    virtual ~Parser();
    void parse();
};

#endif /* PARSER_H_ */
