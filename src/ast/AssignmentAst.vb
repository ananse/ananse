
Option Explicit On
Option Strict On

Imports System

Public Class AssignmentAst
    Implements AstInterface

    private parser as Parser
    private identifier as string
    private expression as Expression

    Public Sub New(parser as Parser)
        MyBase.New
        me.parser = parser
    End Sub

    public sub parse() implements AstInterface.parse
        if parser.lookAhead <> Token.IDENTIFIER then return
        identifier = parser.getLexer().tokenString
        parser.getNextToken()
        parser.match(Token.EQUALS_OPERATOR)
        parser.getNextToken()
        expression = parser.parseExpression
    end sub
End Class

