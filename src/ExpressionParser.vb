
Option Explicit On
Option Strict On

Imports System
Imports System.Collections.Generic

Public Class ExpressionParser

    '
	private parser as Parser
    private shared operators as List (of List (of Token))

	Public Sub New(parser as Parser)
		me.parser = parser
	End Sub

    public function run as Expression
        return parseExpression(0)
    end function

    private function parseExpression(level as integer) as Expression

        dim expression as Expression = new Expression

        if level = operators.Count then
            return parseFactor
        else
            expression = parseExpression(level + 1)
        end if

        do
            if operators(level).indexOf(parser.lookAhead) <> -1 then
                
            end if
        loop

        return expression

    end function

	private function parseFactor as Expression
		
	end function

End Class

private class Expression

    private left as Expression
    private right as Expression

end class

