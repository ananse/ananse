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
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE,
    NODE_INTEGER,
    NODE_FLOAT,
    NODE_IDENTIFIER
} NodeType;

class ExpressionNode {
public:
    ExpressionNode();
    virtual ~ExpressionNode();
    void setIntegerValue(long);
    void setFloatValue(double);
    void setNodeType(NodeType);
    void setLeft(ExpressionNode*);
    void setRight(ExpressionNode*);
    void setDataType(std::string dataType);
    void setIdentifierValue(std::string identifier);
    
    ExpressionNode * getLeft();
    ExpressionNode * getRight();
    bool hasLeft();
    bool hasRight();
    NodeType getType();
    void * getData();
    std::string getDataType();
    long getIntegerValue();
    double getFloatValue();
    std::string getIdentifierValue();
    
private:    
    ExpressionNode * left;
    ExpressionNode * right;
    NodeType type;
    std::string dataType;
    std::string identifierValue;
    long integerValue;
    double floatValue;
};

#endif	/* EXPRESSIONNODE_H */

