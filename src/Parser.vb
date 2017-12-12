
option explicit on
option strict on

imports System

'' Implements the parser for the ananse language
public class Parser

    ' Lexer for tokenizing strings
    Private lexer As Lexer
    Public lookAhead As Token
    Public token As String

    Public ReadOnly expressionParser As ExpressionParser
    Public ReadOnly assignmentParser As AssignmentParser
    Public ReadOnly programParser As ProgramParser

    '' Creates a new Parser by taking in a lexer
    Public Sub New()
        MyBase.new
        expressionParser = New ExpressionParser()
        assignmentParser = New AssignmentParser()
        programParser = New ProgramParser()
    End Sub

    Public sub loadFile(file As String)
        lexer = New Lexer(file)
        lookAhead = lexer.getToken
        token = lexer.tokenString
    End Sub

    Public Function match(token As Token) As Boolean
        If lookAhead = token Then
            Return True
        Else
            Console.WriteLine("Unexpected " + lookAhead.toString + " expecting " + (token.toString()))
            Return False
        End If
    End Function

    Public Function getNextToken() As Token
        lookAhead = lexer.getToken
        Return lookAhead
    End Function

    Public Sub writeUnexpectedError()
        Console.WriteLine("Unexpected '" + lexer.tokenString + "'")
    End Sub

    '' Parse the different statement types
    Public Function run() As AstNode
        Return programParser.parse
    End Function
End Class

