/* 
 * File:   ExpressionNode.h
 * Author: ekow
 *
 * Created on 26 October 2013, 14:12
 */

#ifndef EXPRESSIONNODE_H
#define	EXPRESSIONNODE_H

#include <string>
#include <vector>

typedef enum{
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE,
    NODE_INTEGER,
    NODE_FLOAT,
    NODE_IDENTIFIER,
    NODE_FUNCTION,
    NODE_STRING,
    NODE_EQUALS,
    NODE_NOT_EQUALS,
    NODE_GREATER_THAN,
    NODE_LESS_THAN
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
    void setStringValue(std::string string);
    void setParameters(std::vector<ExpressionNode*> parameters);
    
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
    std::string getStringValue();
    std::vector<ExpressionNode*> getParameters();
    
private:    
    ExpressionNode * left;
    ExpressionNode * right;
    NodeType type;
    std::string dataType;
    std::string identifierValue;
    std::string stringValue;
    long integerValue;
    double floatValue;
    std::vector<ExpressionNode*> parameters;
};

#endif	/* EXPRESSIONNODE_H */

