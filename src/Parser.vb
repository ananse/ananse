
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
	end sub

	public sub run()
		lookAhead = lexer.getToken
		select case lookAhead
			case Token.NUMBER
				
		end select
	end sub

End Class

