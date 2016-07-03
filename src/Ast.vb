
option explicit On
option strict On

imports System

public mustinherit class Ast

	public shared expression as AstInterface

	public shared sub init()
		expression = new ananse.ExpressionAst
	end sub

	public mustoverride sub parse()

end class

