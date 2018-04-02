Option Strict On
Option Explicit On
Imports ananse

Public Class ClassParser
    Inherits AstNodeParser

    Public Overrides ReadOnly Property lookAhead As Token
        Get
            Return Token.CLASS_KEYWORD
        End Get
    End Property

    Public Overrides Function parse() As AstNode
        parser.getNextToken()
        parser.match(Token.IDENTIFIER)
    End Function
End Class
