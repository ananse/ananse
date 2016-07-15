
Option Explicit On
Option Strict On

Imports System



Public Class AssignmentAst
    Implements AstInterface

    private parser as Parser

    Public Sub New(parser as Parser)
        MyBase.New
        me.parser = parser
    End Sub

    public sub parse() implements AstInterface.parse
        dim expression as Expression = parser.parseExpression
        console.writeline(expression.value)
    end sub
End Class

