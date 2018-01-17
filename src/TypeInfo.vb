Option Strict On
Option Explicit On
Imports System.Collections.Generic

Public Class TypeInfo
    Public Property methods As List(Of Method)

    Public Class Method
        Public ReadOnly Property signature As String
    End Class
End Class
