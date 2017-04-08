option explicit on
option strict on

imports System

public class Application

	public shared sub Main()
        Dim parser As Parser = AstNodeParser.init()

        parser.loadFile(Environment.GetCommandLineArgs()(1))
        parser.run()
    End sub

end class
