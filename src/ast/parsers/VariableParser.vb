Option Explicit On
Option Strict On

Public Class VariableParser
    Inherits DeclarationParser

    Public Overrides ReadOnly Property lookAhead As Token
        get
            Return Token.VARIABLE_KEYWORD
        End get
    End property
End Class