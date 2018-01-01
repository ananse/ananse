option explicit on
option strict on

imports System

' Main entry point for the compiler
Public class Application

    Public Shared Sub Main()
        ' Initialize the parser through the astnode
        Dim parser As Parser = AstNodeParser.init()

        ' Create an AST node for the entire program
        Dim program As ProgramNode

        parser.loadFile(Environment.GetCommandLineArgs()(1))
        program = CType(parser.run(), ProgramNode)
    End Sub

End class
