Imports System
Imports ananse

Public Class ProgramParser
    Inherits AstNodeParser

    Public Overrides ReadOnly Property lookAhead As Token
        Get
            Throw New System.NotImplementedException()
        End Get
    End Property

    Private Sub testAndAdd(nodeParser As AstNodeParser, program As ProgramNode)
        If nodeParser.lookAhead = parser.lookAhead Then
            program.statements.Add(nodeParser.parse())
        End If
    End Sub

    Public Overrides Function parse() As AstNode
        Dim program As ProgramNode = New ProgramNode

        Do
            testAndAdd(parser.assignmentParser, program)
            testAndAdd(parser.variableDeclarationParser, program)

            If parser.lookAhead <> Token.NEW_LINE And parser.lookAhead <> Token.EOF Then
                parser.writeUnexpectedError()
                Exit Do
            End If
            If parser.lookAhead = Token.EOF Then Exit Do
            parser.getNextToken()
        Loop

        Return program
    End Function

End Class
