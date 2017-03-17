option explicit on
option strict on

imports System
imports System.IO
imports System.Text.RegularExpressions
imports System.Collections.Generic

' Lexer Class
' Breaks up input file stream into tokens that are consumed by the parser
public class Lexer

	private currentLine as string
	private linePosition as integer
	private characterPosition as integer
	private rules as Dictionary(of Token, string)
    private stream as StreamReader
    public tokenString as string

	public sub new(file as string)
		mybase.new
		rules = new Dictionary(of Token, string)

		rules.Add(Token.NUMBER, "[0-9]+")
        rules.Add(Token.ADD_OPERATOR, "\+")
        rules.Add(Token.SUBTRACT_OPERATOR, "\-")
        rules.Add(Token.MULTIPLY_OPERATOR, "\*")
        rules.Add(Token.DIVIDE_OPERATOR, "/")
        rules.Add(Token.NOT_OPERATOR, "NOT")
        rules.Add(Token.MOD_OPERATOR, "MOD")
        rules.Add(Token.EQUALS_OPERATOR, "=")
        rules.Add(Token.IDENTIFIER, "[a-z][a-z0-9_]*")
        rules.Add(Token.OPEN_PARANTHESIS, "\(")
        rules.Add(Token.CLOSE_PARANTHESIS, "\)")
        rules.Add(Token.NEW_LINE, Environment.NewLine)

		stream = new StreamReader(file)
		currentLine = stream.ReadLine
        linePosition = 1
	end sub

	public function getToken() as Token
		dim regexMatch as Match

		for each rule as KeyValuePair(of Token,string) in rules
            if currentLine = "" then
                currentLine = stream.ReadLine
                if currentLine = nothing then
                    tokenString = "end of file"
                    return Token.EOF
                else
                    tokenString = "new line"
                    linePosition += 1
                    return Token.NEW_LINE
                end if
            end if
			regexMatch = Regex.Match(currentLine, "^" + rule.value)
			if regexMatch.Success then
                tokenString = regexMatch.Value
                currentLine = currentLine.subString(regexMatch.length, currentLine.length - regexMatch.length)
				return rule.key
			end if
		next

		return Token.UNKNOWN
	end function

end class

