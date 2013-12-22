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
    Lexer * lexer;
    SymbolTable * symbolTable;
    Token lookahead;
    Generator * generator;
    
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
    
    // Expressions parsing
    ExpressionNode * parseTerm();
    ExpressionNode * parseFactor();
    ExpressionNode * parseAddition();
    ExpressionNode * parseSubtraction();
    ExpressionNode * parseMultiplication();
    ExpressionNode * parseDivision();
    ExpressionNode * parseExpression();
    
    static bool isNumeric(std::string datatype);
    std::string resolveNumericTypes(std::string left, std::string right);
    void setSource(std::string source);
    
public:
    Parser(Generator * generator, std::string source);
    virtual ~Parser();
    void parse();
};

#endif /* PARSER_H_ */
