option explicit on
option strict on

imports System
imports System.IO
imports System.Text.RegularExpressions

public class Lexer

	private currentLine as string
	private linePosition as integer
	private characterPosition as integer

	public sub new(file as string)
		mybase.new
		dim stream as StreamReader = new StreamReader(file)
		currentLine = stream.ReadLine
	end sub

	public function getToken() as Token
		dim regexMatch as Match = Regex.Match(currentLine, "print")

	end function

end class

