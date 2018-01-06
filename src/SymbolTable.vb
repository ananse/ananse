Option Explicit On
Option Strict On

Imports System.Collections.Generic

Public class Entry
    Public ReadOnly Property name As String
    public ReadOnly Property type As String
    Public ReadOnly Property ns As String
        
    Public Sub New(name As String, type As String, ns As String)
        Me.name = name
        Me.type = type
        Me.ns = ns
    End Sub
End Class

Public Class SymbolTable
    
    Private parent As SymbolTable
    Private entries As Dictionary(Of String, Entry)
    
    Public Sub New 
        entries = New Dictionary(Of String,Entry)
    End Sub
    
    Public Sub insert(name As String, type As String, ns As string)
        entries.Add(name, New Entry(name, type, string))
    End Sub
    
    Public Function exists(name As string) As Boolean
        Return entries.ContainsKey(name)
    End Function
    
End Class
