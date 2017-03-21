
option explicit on
option strict on

imports System

'' Implements the parser for the ananse language
public class Parser

	private lexer as Lexer
	public lookAhead as Token

	public expressionParser as ExpressionParser
    public assignmentAst as AstNode

	'' Creates a new Parser by taking in a lexer
	public sub new()
		mybase.new
		expressionParser = new ExpressionParser()
        assignmentAst = new AssignmentAst()
	end sub

    Public sub loadFile(file As String)
		lexer = new Lexer(file)
		lookAhead = lexer.getToken
    End sub

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

    '' Parse the different statement types
	public sub run()
        do 
    	    assignmentAst.parse()

            if lookAhead <> Token.NEW_LINE and lookAhead <> Token.EOF then
                Console.WriteLine("Unexpected '" + lexer.tokenString + "'")
            end if
            if lookAhead = Token.EOF then exit do
            getNextToken()
        loop
	end sub

End Class

