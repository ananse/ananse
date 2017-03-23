
Option Explicit On
Option Strict On

Imports System

Public mustinherit Class NodeParser
    Private shared _parser As Parser

    Public shared ReadOnly property parser() As Parser
        Get
            If _parser Is Nothing Then 
                _parser = new Parser()
            End If
            Return _parser
        End Get
    end property

    Public mustoverride function parse() as AstNode
End Class

