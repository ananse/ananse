
Option Explicit On
Option Strict On

Public Class ExpressionNode
    Implements AstNode

    Public left As ExpressionNode
    Public right As ExpressionNode
    Public opr As Token
    Public token As Token
    Public value As String
    Public type As String

    Public Function getChildren() As List(Of AstNode) Implements AstNode.getChildren
        Return New List(Of AstNode)({left, right})
    End Function
End Class
