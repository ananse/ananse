Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic
Imports ananse

Public Class Entry
    Public ReadOnly Property name As String
    Public ReadOnly Property type As String
    Public ReadOnly Property ns As String
    Public ReadOnly Property constant As Boolean

    Public Sub New(name As String, type As String, ns As String, constant As Boolean)
        Me.name = name
        Me.type = type
        Me.ns = ns
        Me.constant = constant
    End Sub
End Class

Public Class SymbolTable

    Private parent As SymbolTable
    Private entries As Dictionary(Of String, Entry)

    Public Sub New()
        entries = New Dictionary(Of String, Entry)
    End Sub

    Public Sub insert(name As String, type As String, ns As String, Optional constant As Boolean = False)
        entries.Add(name, New Entry(name, type, ns, constant))
    End Sub

    Public Function exists(name As String) As Boolean
        Return entries.ContainsKey(name)
    End Function

    Public Function lookup(type As String) As Entry
        Return entries(type)
    End Function
End Class
