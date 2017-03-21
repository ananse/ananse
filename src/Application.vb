option explicit on
option strict on

imports System

public class Application

	public shared sub Main()
		dim file as string = Environment.GetCommandLineArgs()(1)
        ExpressionParser.init
		AstNode.parser.loadFile(file)
        AstNode.parser.run
	end sub

end class
