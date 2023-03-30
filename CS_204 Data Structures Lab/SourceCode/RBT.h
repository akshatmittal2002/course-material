#ifndef RBT_H
#define RBT_H
#include "../SourceCode/RBT_node.h"
#include <iostream>
using namespace std;

class RBT
{
    public:
        RBT();
        virtual ~RBT();
        RBT_node* search_tree(int);
        void add_node(RBT_node*);
        void print_inorder();
        int height();
        char colour(int);
        int get_root();
        RBT_node* delete_node(int);

    protected:

    private:
        RBT_node* root;
        RBT_node* nil;
        RBT_node* search_subtree(int,RBT_node*);
        void left_rotation(RBT_node*);
        void right_rotation(RBT_node*);
        void inorder_inside(RBT_node*);
        int height_subtree(RBT_node*);
        void transplant(RBT_node*,RBT_node*);
        RBT_node* minimum(RBT_node*);
};

#endif
