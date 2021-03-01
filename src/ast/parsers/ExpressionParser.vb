
Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic
Imports ananse

' Parses expressions that are used throughout the language
Public Class ExpressionParser
    Inherits AstNodeParser

    'List of operators forming the operator heirachy
    Private Shared operators As List(Of Token()) = New List(Of Token())

    Public Overrides ReadOnly Property lookAhead As Token
        Get
            Throw New NotImplementedException()
        End Get
    End Property

    'Initialize the expression parser and setup operator heirachy
    Public Shared Sub setupOperations()
        operators.Add(New Token() {Token.EQUALS_OPERATOR})
        operators.Add(New Token() {Token.ADD_OPERATOR, Token.SUBTRACT_OPERATOR})
        operators.Add(New Token() {Token.MULTIPLY_OPERATOR, Token.DIVIDE_OPERATOR, Token.MOD_OPERATOR})
    End Sub

    'Run the expression parser and return an expression object
    Public overrides function parse() as AstNode
        return parseExpression(0)
    end function

    private function parseExpression(level as integer) as ExpressionNode
        dim expression as ExpressionNode
        dim tempExpression as ExpressionNode

        if level = operators.Count Then
            ' Return a factor if we've exhausted all operators on our heirachy
            Return parseFactor()
        Else
            ' if not, parse the next level of operators for our expression
            tempExpression = parseExpression(level + 1)
            expression = tempExpression
        end if

        'Loop through all the operators at the current heirachy and group them with their expressions
        do
            if Array.indexOf(operators(level), parser.lookAhead) <> -1 then
                expression = new ExpressionNode
                expression.left = tempExpression
                expression.opr = parser.lookAhead
                parser.getNextToken
                expression.right = parseExpression(level + 1)
            else
                return expression
            end if
            tempExpression = expression
        loop
        return expression
    end function

    ' Factors are numbers, function calls, variables or other expressions contained in parantheses
	private function parseFactor as ExpressionNode
        dim expression as ExpressionNode = New ExpressionNode

		Select Case  parser.lookAhead
		    Case Token.NUMBER
                expression.token = Token.NUMBER
                expression.value = parser.tokenString
                expression.type = "integer"
                parser.getNextToken()
            Case Token.OPEN_PARANTHESIS
                parser.getNextToken
                expression = parseExpression(0)
                parser.match(Token.CLOSE_PARANTHESIS)
                parser.getNextToken()
        End Select
        return expression
	end function
End Class


