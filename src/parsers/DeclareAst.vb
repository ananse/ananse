
Option Explicit On
Option Strict On

Imports System



Public Class DeclareAst
    Implements AstInterface

    private parser as Parser
 
    Public Sub New(parser as Parser)
        MyBase.New
        me.parser = parser
    End Sub

    public sub parse() implements AstInterface.parse
        if parser.lookAhead <> Token.DIM_KEYWORD then return
        parser.getNextToken()
        parser.match(Token.IDENTIFIER)
    end sub
End Class

