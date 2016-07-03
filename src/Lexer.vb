option explicit on
option strict on

imports System
imports System.IO
imports System.Text.RegularExpressions
imports System.Collections.Generic

public class Lexer

	private currentLine as string
	private linePosition as integer
	private characterPosition as integer
	private rules as Dictionary(of Token, string)

	public sub new(file as string)
		mybase.new
		rules = new Dictionary(of Token, string)
		rules.Add(Token.NUMBER, "[0-9]")
		dim stream as StreamReader = new StreamReader(file)
		currentLine = stream.ReadLine
	end sub

	public function getToken() as Token
		dim regexMatch as Match

		'for index as integer 1 to 5
		'	regexMatch = 
		'next

		for each rule as KeyValuePair(of Token,string) in rules
			regexMatch = Regex.Match(currentLine, rule.value)
			if regexMatch.Success then
				return rule.key
			end if
		next

		return Token.UNKNOWN
	end function

end class

