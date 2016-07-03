
Option Explicit On
Option Strict On

Imports System

Public Class ExpressionAst
	Implements AstInterface

	private parser as Parser

	Public Sub New(parser as Parser)
		me.parser = parser
	End Sub

	Sub parse() implements AstInterface.parse
		parser.match(Token.NUMBER)
	End Sub

	private sub parseTerm()
		
	end sub

End Class

