
Option Explicit On
Option Strict On

Public Interface AstNode
    ' Returns the children of the current AST node
    Function getChildren() As List(Of AstNode)
End Interface

