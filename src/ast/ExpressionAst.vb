
Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic

Public Class ExpressionAst
	Implements AstInterface

	private parser as Parser
    private shared operators as List (of Token)

	Public Sub New(parser as Parser)
		me.parser = parser
	End Sub

	Sub parse() implements AstInterface.parse
		parser.match(Token.NUMBER)
	End Sub

	private sub parseTerm()
		
	end sub

End Class

private class Expression

    private left as Expression
    private right as Expression

end class

