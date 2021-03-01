

Option Explicit On
Option Strict On

Imports System
Imports ananse

Public Class AssignmentParser
    Inherits AstNodeParser

    Public Overrides ReadOnly Property lookAhead As Token
        Get
            Return Token.IDENTIFIER
        End Get
    End Property

    Public Overrides Function parse() As AstNode
        Dim node As AssignmentNode = New AssignmentNode
        node.identifier = parser.tokenString
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        node.expression = CType(parser.expressionParser.parse(), ExpressionNode)

        Return node
    End Function
End Class

