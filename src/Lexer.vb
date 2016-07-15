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
    public tokenString as string

	public sub new(file as string)
		mybase.new
		rules = new Dictionary(of Token, string)
		rules.Add(Token.NUMBER, "[0-9]+")
        rules.Add(Token.ADD_OPERATOR, "\+")
        rules.Add(Token.SUBTRACT_OPERATOR, "\-")
		dim stream as StreamReader = new StreamReader(file)
		currentLine = stream.ReadLine
	end sub

	public function getToken() as Token
		dim regexMatch as Match

		for each rule as KeyValuePair(of Token,string) in rules
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

