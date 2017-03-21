

Option Explicit On
Option Strict On

Imports System

Public Class AssignmentAst 
    Inherits AstNode

    private identifier as string
    private expression as Expression

    public overrides sub parse() 
        if parser.lookAhead <> Token.IDENTIFIER then return
        identifier = parser.getLexer().tokenString
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        expression = parser.parseExpression
    end sub
End Class

