Imports ananse

Public Class DeclareParser
    Inherits AstNodeParser

    Public Overrides Function parse() As AstNode
        If parser.lookAhead <> Token.DECLARE_KEYWORD Then Return Nothing
        Dim node As DeclareNode = New DeclareNode

    End Function
End Class
