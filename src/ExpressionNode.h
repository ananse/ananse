/* 
 * File:   ExpressionNode.h
 * Author: ekow
 *
 * Created on 26 October 2013, 14:12
 */

#ifndef EXPRESSIONNODE_H
#define	EXPRESSIONNODE_H

#include <string>

typedef enum{
    SIMPLE_NODE_BINARY_OPERATOR,
    SIMPLE_NODE_INTEGER
} SimpleNodeType;

typedef enum{
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE,
    NODE_INTEGER
} NodeType;

class ExpressionNode {
public:
    ExpressionNode();
    virtual ~ExpressionNode();
    void setData(int);
    void setData(NodeType);
    void setLeft(ExpressionNode*);
    void setRight(ExpressionNode*);
    ExpressionNode * getLeft();
    ExpressionNode * getRight();
    bool hasLeft();
    bool hasRight();
    NodeType getType();
    void * getData();
    std::string getDataType();
    void setDataType(std::string dataType);
    
private:    
    ExpressionNode * left;
    ExpressionNode * right;
    NodeType type;
    std::string dataType;
    void * data;
};

#endif	/* EXPRESSIONNODE_H */

