
option explicit on
option strict on

imports System

public class Parser

	private lexer as Lexer
	private lookAhead as Token

	' Lexer
	' 
	public sub new(Lexer as Lexer)
		mybase.new
		me.lexer = Lexer
		lexer.getToken
	end sub

	public sub run()
		Ast.expression.parse
	end sub

End Class

