#ifndef BST_H
#define BST_H
#include "../SourceCode/BST_node.h"
#include <iostream>
using namespace std;

class BST
{
    public:
        BST();
        virtual ~BST();
        void add_node(BST_node*);
        void print_inorder();
        void print_preorder();
        void print_postorder();
        BST_node* search_tree(int);
        BST_node* minimum();
        BST_node* maximum();
        BST_node* succ(int);
        BST_node* pred(int);
        BST_node* delete_node(int);
        int height();

    protected:

    private:
        BST_node* root;
        void inorder_inside(BST_node*);
        void preorder_inside(BST_node*);
        void postorder_inside(BST_node*);
        BST_node* search_inside(int,BST_node*);
        BST_node* minimum_inside(BST_node*);
        BST_node* maximum_inside(BST_node*);
        BST_node* succ_inside(int,BST_node*);
        BST_node* pred_inside(int,BST_node*);
        int height_subtree(BST_node*);
};

#endif
