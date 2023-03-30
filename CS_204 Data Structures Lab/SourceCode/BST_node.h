#ifndef BST_NODE_H
#define BST_NODE_H
#include <iostream>
using namespace std;

class BST_node
{
    public:
        BST_node(int);
        virtual ~BST_node();
        int getdata();
        void setdata(int);
        void setleft(BST_node*);
        void setright(BST_node*);
        void setparent(BST_node*);
        BST_node* getparent();
        BST_node* getleft();
        BST_node* getright();

    protected:

    private:
        int data;
        BST_node* left;
        BST_node* right;
        BST_node* parent;
};

#endif
