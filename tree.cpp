#include "tree.h"
#include "board.h"

#include <queue>
#include <vector>

// Default constructor
Tree::Tree()
{
    root = NULL;
}

Tree::Tree(const Board & b) {
    root = new Node;
    root->board = b;
    root->score = 0;
    root->parent = NULL;
}

//void Tree::insertOne(Node* & root, const Board & b) {
//    Node *n = new Node;
//    n->board = b;
//    root->children.push_back(n);
//}

Tree::~Tree()
{
    if (root == NULL)   return;
    
    std::queue<Node*> q;
    q.push(root);
    
    Node * cur = NULL;
    
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        
        for (int i = 0; i < cur->children.size(); i++) {
            q.push(cur->children[i]);
        }
        
        delete cur;
    }
    
    root = NULL;
    
    //printf("Destructor called\n");
}
