

Option Explicit On
Option Strict On

Imports System

Public Class AssignmentParser
    Inherits NodeParser

    private identifier as string
    private expression as ExpressionNode

    public overrides sub parse() 
        if parser.lookAhead <> Token.IDENTIFIER then return
        identifier = parser.getLexer().tokenString
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        expression = parser.getExpressionParser().parse()
    end sub
End Class

