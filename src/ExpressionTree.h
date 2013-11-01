/* 
 * File:   ExpressionTree.h
 * Author: ekow
 *
 * Created on 26 October 2013, 14:12
 */

#ifndef EXPRESSIONTREE_H
#define	EXPRESSIONTREE_H

typedef enum{
    NODE_BIN_OPR_ADD,
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
private:    
    ExpressionTree * left;
    ExpressionTree * right;
    NodeType type;
    void * data;
};

#endif	/* EXPRESSIONTREE_H */

