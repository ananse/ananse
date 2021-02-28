
Option Explicit On
Option Strict On

Public Class AssignmentNode
    Implements AstNode

    Public identifier As String
    Public expression As ExpressionNode

    Public Function getChildren() As List(Of AstNode) Implements AstNode.getChildren
        Return New List(Of AstNode)({expression})
    End Function
End Class
