#ifndef TREE_H
#define TREE_H

#include <vector>
#include "board.h"

struct Node {
    Board board;
    Node * parent;
    int score;
    std::vector<Node *> children;
};

class Tree
{
public:
    Node * root;
    
public:
    Tree();
    
    Tree(const Board & b);
    
//    void insertOne(Node* & root, const Board & b);
    
    ~Tree();
    
};

#endif
