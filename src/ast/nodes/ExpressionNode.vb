
Option Explicit On
Option Strict On

Public Class ExpressionNode
    Implements AstNode

    Public left As ExpressionNode
    Public right As ExpressionNode
    Public opr As Token
    Public token As Token
    Public value As String

End Class
