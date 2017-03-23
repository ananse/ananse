
option explicit on
option strict on

imports System

'' Implements the parser for the ananse language
public class Parser

	private lexer as Lexer
	public lookAhead as Token

	private expressionParser as ExpressionParser
    private assignmentParser as AssignmentParser

	'' Creates a new Parser by taking in a lexer
	public sub new()
		mybase.new
		expressionParser = new ExpressionParser()
        assignmentParser = new AssignmentParser()
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

    public function getExpressionParser() as ExpressionParser
        return expressionParser
    end function

    '' Parse the different statement types
	public sub run()
        do 
    	    assignmentParser.parse()

            if lookAhead <> Token.NEW_LINE and lookAhead <> Token.EOF then
                Console.WriteLine("Unexpected '" + lexer.tokenString + "'")
            end if
            if lookAhead = Token.EOF then exit do
            getNextToken()
        loop
	end sub

End Class

