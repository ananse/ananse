#include <Parser.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "generators/js/JsGenerator.h"
#include "LexerException.h"


Parser::OperatorLevel Parser::operators[] = {
	{{EQUALS, NOT_EQUALS}, {NODE_EQUALS, NODE_NOT_EQUALS}, 2},
    {{GREATER_THAN, LESS_THAN}, {NODE_GREATER_THAN, NODE_LESS_THAN}, 2},
	{{PLUS, MINUS}, {NODE_ADD, NODE_SUBTRACT}, 2},
	{{MULTIPLY, DIVIDE}, {NODE_MULTIPLY, NODE_DIVIDE}, 2}
};

int Parser::numOperators;

std::vector<Token> Parser::ifTerminators;
std::vector<Token> Parser::caseTerminators;
std::vector<Token> Parser::forTerminators;
std::vector<Token> Parser::whileTerminators;
std::vector<Token> Parser::doTerminators;
std::vector<Token> Parser::subTerminators;

Parser::Parser(Generator * generator, std::string source)
{
    this->generator = generator;
    Parser::numOperators = sizeof(operators) / sizeof(OperatorLevel);

    ifTerminators.push_back(END);
    ifTerminators.push_back(ELSE_IF);
    ifTerminators.push_back(ELSE);
    caseTerminators.push_back(CASE);
    caseTerminators.push_back(END);
    forTerminators.push_back(NEXT);
    whileTerminators.push_back(END);
    whileTerminators.push_back(WEND);
    doTerminators.push_back(LOOP);
    subTerminators.push_back(END);
    
    selectCases = 0;
    forLoops = 0;
    
    symbols = new Symbols();
    setSource(source);    
}

Parser::~Parser()
{
    symbols->exitScope();
    delete symbols;
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

Symbol * Parser::insertSymbol(Parameter parameter)
{
    Symbol * symbol = symbols->insert(parameter.identifier, parameter.datatype);
    switch(symbols->getStatus())
    {
        case ADDED:
            if(parameter.datatype == "integer")
            {
                symbol->setAsNumber();
            }
            return symbol;
        case EXISTS:
            error(parameter.identifier + " has already been declared");
    }
}

Symbol * Parser::lookupSymbol(std::string identifier)
{
    Symbol * symbol = symbols->lookup(identifier);
    if(symbol == NULL)
    {
        error("Unknown identifier `" + identifier + "`");
    }
    return symbol;
}

void Parser::setSource(std::string source)
{
    try{
        lexer = new Lexer(source);        
        symbols->addType("integer", "primitive");
        symbols->addType("long", "primitive");
        symbols->addType("short", "primitive");
        symbols->addType("single", "primitive");
        symbols->addType("double", "primitive");
        symbols->setLexer(lexer);
        symbols->enterScope(source);
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

void Parser::parseStatement()
{
    parseIdentifierStatements();
    parsePrint();
    parseExit();
    parseContinue();
    parseReturn();
}

void Parser::parse()
{
	std::vector<Token> terminators;
	parse(terminators);
}

void Parser::parse(std::vector<Token> terminators)
{
    do
    {
    	parseStatement();
        parseDeclaration();
        parseIf();
        parseSelectCase();
        parseForLoop();
        parseWhileLoop();
        parseDoLoop();
        parseSubFunction();
        
        // Detect the end of parsing of this block
        for(std::vector<Token>::iterator i = terminators.begin(); i != terminators.end(); i++)
        {
        	if(lookahead == *i) return;
        }

        // Detect newlines or EOFs
        if(lookahead != NEW_LINE && lookahead != END_OF_FILE)
        {
            error("Unexpected token '" + lexer->getTokenString() + "'");
        }

        // Get the next token
        getToken();
        
        // Detect EOFs
        if(lookahead == END_OF_FILE) break;
        
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
        error(
            "Unexpected " +
            Lexer::describeToken(lookahead) +
            " '" + lexer->getTokenString() + "'. Expected " +
            Lexer::describeToken(token) + "."
        );
    }
}

void Parser::parseDeclaration()
{
    if (lookahead == DIM)
    {
        /*std::string identifier;
        std::string datatype;*/
    
        do{
            Parameter parameter;
            
            getToken();
            match(IDENTIFIER);
            parameter.identifier = lexer->getIdentifierValue();
            getToken();

            if(lookahead == AS)
            {
                getToken();
                match(IDENTIFIER);
                parameter.datatype = lexer->getIdentifierValue();
                getToken();
            }
            else
            {
                error("Expected AS followed by the datatype");
            }
            
            if(!symbols->vaildateType(parameter.datatype))
            {
                error("Unknown data type `" + parameter.datatype + "`");
            }
            
            currentSymbol = insertSymbol(parameter);
            generator->emitDeclaration(parameter);
            parseAssignment();
            generator->emitEndOfStatement();                        
        }
        while(lookahead == COMMA);
    }
}

void Parser::parseContinue()
{
    if(lookahead == CONTINUE)
    {
        getToken();
        if(lookahead == FOR && forLoops > 0)
        {
            generator->emitContinueFor();
            getToken();
        }
        else if(lookahead == WHILE && whileLoops > 0)
        {
            generator->emitContinueWhile();
            getToken();
        }
    }
}

void Parser::parseExit()
{
    if(lookahead == EXIT)
    {
        getToken();
        if(lookahead == SELECT && selectCases > 0)
        {
            generator->emitExitSelect();
            getToken();
        }
        else if(lookahead == FOR && forLoops > 0)
        {
            generator->emitExitFor();
            getToken();
        }
        else if(lookahead == WHILE && whileLoops > 0)
        {
            generator->emitExitWhile();
            getToken();
        }        
        else if(lookahead == FUNCTION && functions > 0)
        {
            //generator->emitExitFunction();
            getToken();
        }
        else if(lookahead == NEW_LINE)
        {
            // Exit the app
        }
    }
}

void Parser::parseAssignment()
{
    if(lookahead == EQUALS)
    {
        getToken();
        generator->emitAssignment();
        ExpressionNode * expression = parseExpression();
        
        if(isNumeric(expression->getDataType()) && isNumeric(currentSymbol->getDataType()))
        {
            generator->emitExpression(expression);
        }
        else if(expression->getDataType() == currentSymbol->getDataType())
        {
            generator->emitExpression(expression);
        }        
        else if(currentSymbol->getDataType() == "")
        {
            currentSymbol->setDataType(expression->getDataType());
            generator->emitExpression(expression);
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
                generator->write(identifier);
                parseAssignment();
                generator->emitEndOfStatement();
                break;
            case NEW_LINE:
            case BRACKET_OPEN:
                if(currentSymbol->getCallable())
                {
                    ExpressionNodeList parameters;
                    ParameterList expectedParameters = currentSymbol->getParameterList();
                    if(lookahead == BRACKET_OPEN)
                    {
                        do{
                            getToken();
                            parameters.push_back(parseExpression());
                        } while(lookahead == COMMA);
                        match(BRACKET_CLOSE);
                        getToken();
                    }
                    
                    if(parameters.size() != expectedParameters.size())
                    {
                        std::stringstream errorMessage;
                        errorMessage<<"Expected "<<expectedParameters.size()<<" parameter(s) for "<<currentSymbol->getIdentifier()<<"  but found "<<parameters.size();
                        error(errorMessage.str());
                    }
                    else
                    {
                        ExpressionNodeListIterator p;
                        ParameterListIterator e;
                        int count;
                        for(
                            p = parameters.begin(), 
                            e = expectedParameters.begin(),
                            count = 1;
                            p != parameters.end(); p++, e++, count++
                        )
                        {
                            if((*p)->getDataType() != (*e).datatype)
                            {
                                std::stringstream errorMessage;
                                errorMessage<<"The datatype for argument "<<count<<" of "<<currentSymbol->getIdentifier()<<" does not match. Expected: "<<(*e).datatype<<", found "<<(*p)->getDataType()<<".";
                                error(errorMessage.str());
                            }
                        }
                    }
                    generator->emitCallSubFunction(currentSymbol->getIdentifier(), parameters);
                    generator->emitEndOfStatement();
                }
                break;
        }
    }
}

void Parser::parsePrint()
{
    if(lookahead == PRINT)
    {
        ExpressionNode * expression;
		getToken();
		expression = parseExpression();
		generator->emitPrint();
		generator->emitExpression(expression);
		generator->emitEndOfStatement();
	}
}

void Parser::parseSubFunction()
{
    if(lookahead == FUNCTION)
    {
        Parameter function;
        ParameterList parameters;
        Symbol * symbol;
        
        getToken();
        match(IDENTIFIER);
        function.identifier = lexer->getIdentifierValue();
        getToken();
        match(BRACKET_OPEN);
        
        do
        {
            getToken();
            if(lookahead == IDENTIFIER)
            {
                Parameter parameter;
                parameter.identifier = lexer->getIdentifierValue();
                getToken();
                match(AS);
                getToken();
                match(IDENTIFIER);
                parameter.datatype = lexer->getIdentifierValue();
                parameters.push_back(parameter);
                getToken();
            }
        }
        while(lookahead == COMMA);
        
        match(BRACKET_CLOSE);
        getToken();
        match(AS);
        getToken();
        match(IDENTIFIER);
        function.datatype = lexer->getIdentifierValue();
        symbol = insertSymbol(function);
        symbol->setCallable(true);
        symbol->setParameterList(parameters);
        
        symbols->enterScope("function");
        
        for(ParameterListIterator i = parameters.begin(); i != parameters.end(); i++)
        {
            insertSymbol(*i);
        }
        
        getToken();
        match(NEW_LINE);
        
        generator->emitFunction(function, parameters);
        generator->emitBeginCodeBlock();
        functions++;
        
        parse(subTerminators);
                
        if(lookahead == END)
        {
            functions--;
            getToken();
            match(FUNCTION);
            generator->emitEndCodeBlock();
            symbols->exitScope();
            generator->emitEndFunction();
            getToken();
        }
    }
}

void Parser::parseIf()
{
	// Funny if block handler repeats code all over the place
	if(lookahead == IF)
	{
		getToken();
		ExpressionNode * condition = parseExpression();

		generator->emitIf(condition);

		if(lookahead == THEN)
		{
			getToken();
		}

		// Deal with multiline if syntax
		if(lookahead == NEW_LINE)
		{
			generator->emitBeginCodeBlock();
			parse(ifTerminators);

			while(lookahead == ELSE_IF)
			{
				getToken();
				ExpressionNode * condition = parseExpression();
                
				if(lookahead == THEN)
				{
					getToken();
				}
                
				if(lookahead == NEW_LINE)
				{
					generator->emitEndCodeBlock();
					generator->emitElseIf(condition);
					generator->emitBeginCodeBlock();
                    symbols->enterScope("if");
					parse(ifTerminators);
                    symbols->exitScope();
				}
			}

			if(lookahead == ELSE)
			{
				getToken();
				generator->emitEndCodeBlock();
				generator->emitElse();
				generator->emitBeginCodeBlock();
				parse(ifTerminators);
			}

			if(lookahead == END)
			{
				getToken();
				if(lookahead == IF)
				{
					generator->emitEndCodeBlock();
					getToken();
				}
				else if(lookahead == NEW_LINE)
				{
					generator->emitEndProgramme();
				}
			}
			else
			{
				error("Expecting END IF or ELSEIF or ELSE");
			}
		}
        
        // Deal with single line if syntax
		else
		{
			parseStatement();
			while(lookahead == ELSE_IF)
			{
				getToken();
				ExpressionNode * condition = parseExpression();
				generator->emitElseIf(condition);
				if(lookahead == THEN)
				{
					getToken();
				}
				parseStatement();
			}
			if(lookahead == ELSE)
			{
				generator->emitElse();
				getToken();
				parseStatement();
			}
		}
	}
}

CaseExpression * Parser::parseCaseExpression()
{
    CaseExpression * caseExpression;
    ExpressionNode * expression1;
    ExpressionNode * expression2;
    CaseExpressionType type;
    Token comparator;
    
    if(lookahead == IS)
    {
        type = CASE_IS;
        getToken();
        if(!isComparator(lookahead)) error("Expecting comparator after IS statement");            
        comparator = lookahead;
        expression1 = parseExpression();
    }
    else
    {
        type = CASE_EXPRESSION;
        expression1 = parseExpression();
    
        if(lookahead == TO)
        {
            type = CASE_TO;
            getToken();
            expression2 = parseExpression();
        }
    }
    caseExpression = new CaseExpression(type, expression1, expression2);
    if(isComparator(comparator))
    {
        caseExpression->setComparator(comparator);
    }
    return caseExpression;
}

void Parser::parseWhileLoop()
{
    if(lookahead == WHILE)
    {
        ExpressionNode * whileExpression = NULL;
        bool whileEnded = false;
        
        whileLoops++;
        getToken();
        whileExpression = parseExpression();
        generator->emitWhile(whileExpression);
        
        match(NEW_LINE);
        getToken();

        generator->emitBeginCodeBlock();
        symbols->enterScope("while");        
        parse(whileTerminators);
        symbols->exitScope();
        generator->emitEndCodeBlock();
        
        if(lookahead == END)
        {
            getToken();
            if(lookahead == WHILE)
            {
                whileEnded = true;
            }
        }
        else if(lookahead == WEND)
        {
            whileEnded = true;
        }
        
        if(whileEnded)
        {
            generator->emitEndWhile();
            getToken();            
        }
    }
}

void Parser::parseDoLoop()
{
    if(lookahead == DO)
    {
        std::string doType = "";
        ExpressionNode * doCondition = NULL;
        
        getToken();
        
        switch(lookahead)
        {
            case WHILE:
                getToken();
                doType = "while";
                doCondition = parseExpression();
                break;
                
            case UNTIL:
                getToken();
                doType = "until";
                doCondition = parseExpression();
                break;
        }
        
        generator->emitDo(doType, doCondition);
        generator->emitBeginCodeBlock();
        symbols->enterScope("do");
        parse(doTerminators);
        symbols->exitScope();
        generator->emitEndCodeBlock();
        
        if(lookahead == LOOP)
        {
            std::string loopType = "";
            ExpressionNode * loopCondition = NULL;            
            getToken(); 
            
            if(doType == "")
            {
                switch(lookahead)
                {
                    case WHILE:
                        getToken();
                        loopType = "while";
                        loopCondition = parseExpression();
                        break;

                    case UNTIL:
                        getToken();
                        loopType = "until";
                        loopCondition = parseExpression();
                        break;
                }                
            }
            
            generator->emitLoop(loopType, loopCondition);
        }
    }
}

void Parser::parseForLoop()
{
    if(lookahead == FOR)
    {
        forLoops++;
        std::string identifier;
        Symbol * counter;
        ExpressionNode * fromExpression = NULL;
        ExpressionNode * toExpression = NULL;
        ExpressionNode * stepExpression = NULL;
        
        getToken();
        match(IDENTIFIER);
        identifier = lexer->getIdentifierValue();
        getToken();
        
        if(lookahead == AS)
        {
            // Add the symbol to the symbol table
            Parameter parameter;
            getToken();
            parameter.identifier = identifier;
            parameter.datatype = lexer->getIdentifierValue();
            counter = insertSymbol(parameter);
            generator->emitDeclaration(parameter);
            getToken();
        }
        else
        {
            counter = lookupSymbol(identifier);
        }
        
        match(EQUALS);
        getToken();
        
        fromExpression = parseExpression();
        match(TO);
        getToken();
        toExpression = parseExpression();
        
        if(lookahead == STEP)
        {
            getToken();
            stepExpression = parseExpression();
        }
        
        match(NEW_LINE);
        generator->emitFor(identifier, fromExpression, toExpression, stepExpression);
        getToken();
        
        generator->emitBeginCodeBlock();
        symbols->enterScope("for_next");
        parse(forTerminators);
        symbols->exitScope();
        generator->emitEndCodeBlock();
        
        if(lookahead == NEXT)
        {
            forLoops--;
        }
        
        getToken();
        
    }
}

void Parser::parseSelectCase()
{
    if(lookahead == SELECT)
    {
        selectCases++;
        getToken();
        if(lookahead == CASE) getToken();
        ExpressionNode * expression = parseExpression();
        generator->emitSelect(expression);
        match(NEW_LINE);
        getToken();
        
        while(lookahead == CASE)
        {
            getToken();
            if(lookahead == ELSE)
            {
                getToken();
                generator->emitCaseElse();
                generator->emitBeginCodeBlock();
                symbols->enterScope("case_else");
                parse(caseTerminators);
                symbols->exitScope();
                generator->emitEndCodeBlock();
            }
            else
            {
                std::vector<CaseExpression*> expressions;
                
                do
                {
                    expressions.push_back(parseCaseExpression());
                } while(lookahead == COMMA);
                
                generator->emitCase(expressions);
                generator->emitBeginCodeBlock();
                symbols->enterScope("case");
                parse(caseTerminators);
                symbols->exitScope();
                generator->emitEndCodeBlock();
            }
        }
        
        if(lookahead == END){
            getToken();
            match(SELECT);
            generator->emitEndSelect();
            getToken();
            selectCases--;
        }
    }
}

ExpressionNode * Parser::parseExpression()
{
	return parseBinaryOperators(0, this);
}

ExpressionNode * Parser::parseBinaryOperators(int precedence, Parser * instance)
{
	ExpressionNode *expression;
	if(precedence < numOperators - 1)
	{
		expression = parseBinaryOperators(precedence+1, instance);
	}
	else
	{
		expression = parseUnaryOperators(instance);
	}

    if (expression == NULL) return NULL;

    ExpressionNode *left, *right;
	bool continueLooping;

    do
    {
    	continueLooping = false;

    	for(int i = 0; i < operators[precedence].numOperators; i++)
    	{
    		if(instance->lookahead == operators[precedence].tokens[i])
    		{
                left = expression;
                expression = new ExpressionNode();
                expression->setNodeType(operators[precedence].nodes[i]);
                instance->getToken();

            	if(precedence < numOperators - 1)
            	{
            		right = parseBinaryOperators(precedence+1, instance);
            	}
            	else
            	{
            		right = parseUnaryOperators(instance);
            	}

                expression->setRight(right);
                expression->setLeft(left);

                expression->setDataType(
					instance->resolveTypes(
						left->getDataType(),
						right->getDataType(),
						operators[precedence].nodes[i]
					)
				);
                break;
    		}
    	}

    	for(int i = 0; i < operators[precedence].numOperators; i++)
    	{
    		if(instance->lookahead == operators[precedence].tokens[i])
    		{
    			continueLooping = true;
    			break;
    		}
    	}
    } while (continueLooping);

    return expression;
}

ExpressionNode * Parser::parseUnaryOperators(Parser * instance)
{
    ExpressionNode * factor = NULL;
    switch (instance->lookahead)
    {
        case INTEGER:
            factor = new ExpressionNode();
            factor->setIntegerValue(instance->lexer->getIntegerValue());
            factor->setDataType("integer");
            instance->getToken();
            break;
            
        case SINGLE:
            factor = new ExpressionNode();
            factor->setFloatValue(instance->lexer->getSingleValue());
            factor->setDataType("single");
            instance->getToken();
            break;
            
        case IDENTIFIER:
            factor = new ExpressionNode();
            Symbol * symbol = instance->lookupSymbol(instance->lexer->getIdentifierValue());
            
            if(symbol->getCallable())
            {
                
            }
            else
            {
                factor->setIdentifierValue(instance->lexer->getIdentifierValue());
                factor->setDataType(symbol->getDataType());
                instance->getToken();
            }
            break;

        case BRACKET_OPEN:
            factor = instance->parseExpression();
            instance->match(BRACKET_CLOSE);
            instance->getToken();
            break;

        case STRING:
        	factor = new ExpressionNode();
        	factor->setStringValue(instance->lexer->getStringValue());
        	factor->setDataType("string");
        	instance->getToken();
        	break;
    }
    return factor;
}

bool Parser::isComparator(Token token)
{
    switch(token)
    {
        case EQUALS:
        case NOT_EQUALS:
        case GREATER_THAN:
        case LESS_THAN:
        case GREATER_THAN_OR_EQUALS:
        case LESS_THAN_OR_EQUALS:
            return true;
            
        default:
            return false;
    }
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

std::string Parser::resolveTypes(std::string leftType, std::string rightType, NodeType operatorNodeType)
{
	std::string datatype;

	switch(operatorNodeType)
	{
	case NODE_ADD:
	case NODE_SUBTRACT:
	case NODE_MULTIPLY:
	case NODE_DIVIDE:
		if(leftType == "integer")
		{
			if(rightType == "integer") datatype = "integer";
			if(rightType == "single") datatype = "single";
		}
		else if(leftType == "single")
		{
			if(rightType == "single" || rightType == "integer") datatype = "single";
		}
		break;

	case NODE_EQUALS:
	case NODE_NOT_EQUALS:
		datatype = "boolean";
	}

	return datatype;
}

void Parser::parseReturn()
{
    if(lookahead == RETURN)
    {
        ExpressionNode * returnExpression = NULL;
        getToken();
        if(lookahead != NEW_LINE)
        {
            returnExpression = parseExpression();
        }
        generator->emitReturn(returnExpression);
    }
}
