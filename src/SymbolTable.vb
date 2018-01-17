Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic
Imports ananse

Public Class SymbolTable

    Private parent As SymbolTable
    Private entries As Dictionary(Of String, Entry)

    Public Sub New()
        entries = New Dictionary(Of String, Entry)
    End Sub

    Public Function insert(name As String, type As String, Optional ns As String = "", Optional constant As Boolean = False) As Entry
        Dim entry As Entry = New Entry(name, type, ns, constant)
        entries.Add(name, entry)
        Return entry
    End Function

    Public Function exists(name As String) As Boolean
        Return entries.ContainsKey(name)
    End Function

    Public Function lookup(type As String) As Entry
        Return entries(type)
    End Function

    Public Class Entry
        Public ReadOnly Property name As String
        Public ReadOnly Property type As String
        Public ReadOnly Property ns As String
        Public ReadOnly Property constant As Boolean
        Public Property typeInfo As TypeInfo

        Public Sub New(name As String, type As String, ns As String, constant As Boolean)
            Me.name = name
            Me.type = type
            Me.ns = ns
            Me.constant = constant
            typeInfo = New TypeInfo
        End Sub
    End Class
End Class
