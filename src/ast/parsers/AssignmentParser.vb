

Option Explicit On
Option Strict On

Imports System

Public Class AssignmentParser
    Inherits AstNodeParser

    Public overrides function parse() As AstNode
        if parser.lookAhead <> Token.IDENTIFIER then return Nothing

        Dim node As AssignmentNode = New AssignmentNode
        node.identifier = parser.token
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        node.expression = CType(parser.expressionParser.parse(), ExpressionNode)

        Return node
    end function
End Class

