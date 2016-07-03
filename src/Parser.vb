
option explicit on
option strict on

imports System


public class Parser

	private lexer as Lexer
	private lookAhead as Token

	public expressionParser as AstInterface

	' Lexer
	public sub new(Lexer as Lexer)
		mybase.new
		me.lexer = Lexer

		expressionParser = new ExpressionAst(me)

		lookAhead = lexer.getToken
	end sub

	public function match(token as Token) as boolean
		if lookAhead = token then 
			return true
		else
			Console.WriteLine("Unexpected " + lookAhead.toString)
			return false
		end if
	end function

	public function getLexer() as Lexer
		return lexer
	end function

	public sub run()
		expressionParser.parse
	end sub

End Class

