
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
    Public symbolTable As SymbolTable

    Public Sub New()
        MyBase.new
        expressionParser = New ExpressionParser()
        assignmentParser = New AssignmentParser()
        programParser = New ProgramParser()
        variableDeclarationParser = New VariableParser()
        symbolTable = New SymbolTable()
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
            writeError("There was an unexpected " + If(lookAhead = ananse.Token.UNKNOWN, lexer.tokenString, lookAhead.ToString()) + " instead of " + (token.ToString()))
            Return False
        End If
    End Function

    Public Sub writeError(errorMessage As String)
        Console.Error.WriteLine($"{lexer.fileAddress}: {errorMessage}")
        Environment.Exit(1)
    End Sub

    Public Function getNextToken() As Token
        lookAhead = lexer.getToken
        token = lexer.tokenString
        Return lookAhead
    End Function

    Public Sub writeUnexpectedError()
        writeError("There was an unexpected '" + lexer.tokenString + "'")
    End Sub

    '' Parse the different statement types
    Public Function run() As AstNode
        Return programParser.parse
    End Function
End Class

