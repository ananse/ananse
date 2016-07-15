
Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic

Public Class ExpressionParser

    'An instance of the parser
	private parser as Parser

    'List of operators forming the operator heirachy
    'private shared operators as List (of List (of Token)) = new List (of List (of Token))
    private shared operators as List (of Token()) = new List (of Token())

    public shared sub init
        operators.add(new Token() {Token.ADD_OPERATOR, Token.SUBTRACT_OPERATOR})
        operators.add(new Token() {Token.MULTIPLY_OPERATOR, Token.DIVIDE_OPERATOR})
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
            return parseFactor
        else
            tempExpression = parseExpression(level + 1)
            expression = tempExpression
        end if
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

private class Expression

    public left as Expression
    public right as Expression
    public opr as Token
    public token as Token
    public value as string

end class

