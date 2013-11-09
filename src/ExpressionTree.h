/* 
 * File:   ExpressionTree.h
 * Author: ekow
 *
 * Created on 26 October 2013, 14:12
 */

#ifndef EXPRESSIONTREE_H
#define	EXPRESSIONTREE_H

typedef enum{
    SN_BIN_OP,
    SN_INT
} SimpleNodeType;

typedef enum{
    NODE_BIN_OPR_ADD,
    NODE_BIN_OPR_SUBTRACT,
    NODE_BIN_OPR_MULTIPLY,
    NODE_BIN_OPR_DIVIDE,
    NODE_INTEGER
} NodeType;

class ExpressionTree {
public:
    ExpressionTree();
    virtual ~ExpressionTree();
    void setData(int);
    void setData(NodeType);
    void setLeft(ExpressionTree*);
    void setRight(ExpressionTree*);
    
    NodeType getType();
private:    
    ExpressionTree * left;
    ExpressionTree * right;
    NodeType type;
    void * data;
};

#endif	/* EXPRESSIONTREE_H */

