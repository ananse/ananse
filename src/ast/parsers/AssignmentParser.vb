

Option Explicit On
Option Strict On

Imports System

Public Class AssignmentParser
    Inherits NodeParser

    private identifier as string
    private expression as ExpressionNode

    public overrides function parse() As AstNode
        if parser.lookAhead <> Token.IDENTIFIER then return Nothing
        identifier = parser.getLexer().tokenString
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        expression = CType(parser.getExpressionParser().parse(), ExpressionNode)
    end function
End Class

