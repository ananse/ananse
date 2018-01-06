Option Explicit On
Option Strict On

Public MustInherit Class DeclarationParser
    Inherits AstNodeParser

    Public Overrides Function parse() As AstNode
        
        Dim node As DeclareNode = New DeclareNode
        
        node.declaration = parser.lookAhead
        parser.getNextToken()
        parser.match(Token.IDENTIFIER)
        node.name = parser.token
        parser.getNextToken()
        
        If parser.lookAhead = Token.AS_KEYWORD Then
            parser.getNextToken()
            parser.match(Token.IDENTIFIER)
            node.type = parser.token
            parser.getNextToken()
        End If
        
        If parser.lookAhead = Token.EQUALS_OPERATOR Then
            parser.getNextToken()
            node.initialization = CType(parser.expressionParser.parse(), ExpressionNode)
        
        End If
        
        Return node
        
    End Function
End Class
