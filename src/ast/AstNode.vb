
Option Explicit On
Option Strict On

Imports System

Public Interface AstNode
    Public Function getChildren() as List(of AstNode)
End Interface

