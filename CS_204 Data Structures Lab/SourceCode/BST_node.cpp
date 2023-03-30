#include "BST_node.h"

BST_node::BST_node(int value)
{
    data = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
int BST_node::getdata()
{
    return data;
}
void BST_node::setdata(int value)
{
    data = value;
}
void BST_node::setleft(BST_node* node)
{
    left = node;
}
void BST_node::setright(BST_node* node)
{
    right = node;
}
void BST_node::setparent(BST_node* node)
{
    parent = node;
}
BST_node* BST_node::getparent()
{
    return parent;
}
BST_node* BST_node::getleft()
{
    return left;
}
BST_node* BST_node::getright()
{
    return right;
}
BST_node::~BST_node()
{
    return;
}
