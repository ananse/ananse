Public Class ProgramParser
    Inherits AstNodeParser

    Private Sub add(node As AstNode, program As ProgramNode)
        program.statements.Add(node)
    End Sub

    Public Overrides Function parse() As AstNode
        Dim program As ProgramNode = New ProgramNode

        Do
            add(parser.assignmentParser.parse(), program)

            If parser.lookAhead <> Token.NEW_LINE And parser.lookAhead <> Token.EOF Then
                parser.writeUnexpectedError()
            End If
            If parser.lookAhead = Token.EOF Then Exit Do
            parser.getNextToken()
        Loop

        Return program
    End Function

End Class
