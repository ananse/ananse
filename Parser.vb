
option explicit on
option strict on

imports System



public class Parser

	private Lexer as Lexer
	
	public sub new(Lexer as Lexer)
		mybase.new
		me.Lexer = Lexer
	end sub

	public sub parse()

	end sub

End Class

