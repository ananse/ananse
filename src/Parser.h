#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>

#include "Lexer.h"
#include "ExpressionNode.h"
#include "generators/Generator.h"
#include "Symbols.h"
#include "CaseExpression.h"

class Parser
{
private:

    typedef struct{
        Token tokens[4];
        NodeType nodes[4];
        int numOperators;
    } OperatorLevel;

    Lexer * lexer;
    Symbols * symbols;
    Token lookahead;
    Generator * generator;

    static OperatorLevel operators[];
    static int numOperators;
    static std::vector<Token> ifTerminators;
    static std::vector<Token> caseTerminators;
    
    bool match(Token token);
    void getToken();

    void out(std::string type, std::string message);
    void error(std::string message);
    
    Symbol * lookupSymbol(std::string identifier);
    Symbol * insertSymbol(std::string identifier, std::string type);
    Symbol * currentSymbol;
    
    void parseStatement();
    void parseDeclaration();
    void parseAssignment();
    void parseIdentifierStatements();
    void parsePrint();
    void parseIf();
    void parseSelectCase();
    CaseExpression * parseCaseExpression();
    
    // Expressions parsing
    ExpressionNode * parseExpression();
    static ExpressionNode * parseBinaryOperators(int precedence, Parser * instance);
    static ExpressionNode * parseUnaryOperators(Parser * instance);
    
    static bool isNumeric(std::string datatype);
    static bool isComparator(Token token);
    std::string resolveTypes(std::string leftType, std::string rightType, NodeType operatorNodeType);
    void setSource(std::string source);
    
public:
    Parser(Generator * generator, std::string source);
    virtual ~Parser();
    void parse(std::vector<Token> terminators);
    void parse();
};

#endif /* PARSER_H_ */
