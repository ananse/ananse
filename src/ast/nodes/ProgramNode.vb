Imports System.Collections.Generic

Public Class ProgramNode
    Implements AstNode
    Public statements As List(Of AstNode) = New List(Of AstNode)

    Public Function getChildren() As List(Of AstNode) Implements AstNode.getChildren
        return statements
    End Function
End Class
