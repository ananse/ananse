
option explicit on
option strict on

imports System


public class Parser

	private lexer as Lexer
	public lookAhead as Token

	public expressionParser as ExpressionParser
    public assignmentAst as AstInterface

	' Lexer
	public sub new(Lexer as Lexer)
		mybase.new
		me.lexer = Lexer
		expressionParser = new ExpressionParser(me)
        assignmentAst = new AssignmentAst(me)
		lookAhead = lexer.getToken
	end sub

	public function match(token as Token) as boolean
		if lookAhead = token then 
			return true
		else
			Console.WriteLine("Unexpected " + lookAhead.toString + " expecting " + (token.toString()))
			return false
		end if
	end function

    public function isOperator(token as Token) as boolean
        
    end function

	public function getLexer() as Lexer
		return lexer
	end function

    public function getNextToken() as Token
        lookAhead = lexer.getToken
        return lookAhead
    end function

    public function parseExpression() as Expression
        return expressionParser.run
    end function

	public sub run()
	    assignmentAst.parse()
        Console.WriteLine("Unexpected '" + lexer.tokenString + "'")
	end sub

End Class

