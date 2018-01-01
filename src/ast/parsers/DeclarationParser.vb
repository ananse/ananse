Option Explicit On
Option Strict On
Imports ananse

Public Class DeclarationParser
    Inherits AstNodeParser

    Public Overrides ReadOnly Property lookAhead As Token
        Get
            Return Token.DECLARE_KEYWORD
        End Get
    End Property

    Public Overrides Function parse() As AstNode
        Dim node As DeclareNode = New DeclareNode

        Return node
    End Function
End Class
