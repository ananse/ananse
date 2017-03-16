
Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic

' Parses expressions that are used throughout the language
Public Class ExpressionParser

    'An instance of the parser
	private parser as Parser

    'List of operators forming the operator heirachy
    private shared operators as List (of Token()) = new List (of Token())

    'Initialize the expression parser and setup operator heirachy
    public shared sub init
        operators.add(new Token() {Token.EQUALS_OPERATOR})
        operators.add(new Token() {Token.ADD_OPERATOR, Token.SUBTRACT_OPERATOR})
        operators.add(new Token() {Token.MULTIPLY_OPERATOR, Token.DIVIDE_OPERATOR, Token.MOD_OPERATOR})
    end sub

	Public Sub New(parser as Parser)
		me.parser = parser
	End Sub

    'Run the expression parser and return an expression object
    public function run as Expression
        return parseExpression(0)
    end function

    private function parseExpression(level as integer) as Expression
        dim expression as Expression
        dim tempExpression as Expression

        if level = operators.Count then
            ' Return a factor if we've exhausted all our operators
            return parseFactor
        else
            ' if not, parse the next level of expressions
            tempExpression = parseExpression(level + 1)
            expression = tempExpression
        end if

        'Loop through all the operators at the current heirachy and group them with their expressions
        do
            if Array.indexOf(operators(level), parser.lookAhead) <> -1 then
                expression = new Expression
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
	private function parseFactor as Expression
        dim expression as Expression = new Expression
		if parser.lookAhead = Token.Number then
            expression.token = Token.Number
            expression.value = parser.getLexer().tokenString
            parser.getNextToken
        end if
        return expression
	end function

End Class

Public Class Expression

    Public left As Expression
    Public right As Expression
    Public opr As Token
    Public token As Token
    Public value As String

End Class

