
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
        parser.parseExpression
    end sub
End Class

