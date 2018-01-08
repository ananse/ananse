Option Explicit On
Option Strict On

Public MustInherit Class DeclarationParser
    Inherits AstNodeParser

    Public Overrides Function parse() As AstNode

        Dim node As DeclareNode = New DeclareNode

        node.declaration = parser.lookAhead
        parser.getNextToken()
        parser.match(Token.IDENTIFIER)
        node.name = parser.token
        parser.getNextToken()

        If parser.lookAhead = Token.AS_KEYWORD Then
            parser.getNextToken()
            parser.match(Token.IDENTIFIER)
            node.type = parser.token
            verifyType(parser.token)
            parser.getNextToken()
        End If

        If parser.lookAhead = Token.EQUALS_OPERATOR Then
            parser.getNextToken()
            node.initialization = CType(parser.expressionParser.parse(), ExpressionNode)
        End If

        Return node

    End Function

    Private Sub verifyType(type As String)
        Dim symbol As Entry
        If Not parser.symbolTable.exists(type) Then
            parser.writeError($"datatype {type} is unknown")
            Return
        End If
        symbol = parser.symbolTable.lookup(type)
        If symbol.type <> "type" Then
            parser.writeError($"{type} is not a datatype")
        End If
    End Sub
End Class
