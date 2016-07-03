option explicit on
option strict on

imports System

public class Application

	public shared sub Main()
		dim file as string = Environment.GetCommandLineArgs()(1)
		dim lexer as Lexer = new Lexer(file)
		dim parser as Parser = new Parser(lexer)
		Ast.init
		parser.run
	end sub

end class
