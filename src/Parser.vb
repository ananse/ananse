
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
    Public ReadOnly variableDeclarationParser As VariableParser
    Public ReadOnly programParser As ProgramParser
    Public ReadOnly symbolTable As SymbolTable

    Public Sub New()
        MyBase.new
        expressionParser = New ExpressionParser()
        assignmentParser = New AssignmentParser()
        programParser = New ProgramParser()
        variableDeclarationParser = New VariableParser()
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
            Console.Error.WriteLine("Unexpected " + If(lookAhead = ananse.Token.UNKNOWN, lexer.tokenString, lookAhead.ToString()) + " expecting " + (token.toString()))
            Return False
        End If
    End Function

    Public Function getNextToken() As Token
        lookAhead = lexer.getToken
        token = lexer.tokenString
        Return lookAhead
    End Function

    Public Sub writeUnexpectedError()
        Console.Error.WriteLine("Unexpected '" + lexer.tokenString + "'")
    End Sub

    '' Parse the different statement types
    Public Function run() As AstNode
        Return programParser.parse
    End Function
End Class

