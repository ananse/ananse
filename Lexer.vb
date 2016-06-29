option explicit on
option strict on

imports System
imports System.IO

public class Lexer

	private source as string

	public sub new(file as string)
		mybase.new
		dim stream as StreamReader = new StreamReader(file)
		source = stream.ReadToEnd
		stream.Close
	end sub

	public function getToken() as Token

	end function

end class

