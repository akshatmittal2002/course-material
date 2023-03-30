#include "RBT_node.h"

RBT_node::RBT_node(int value)
{
    data = value;
    colour = 'r';
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
int RBT_node::getdata()
{
    return data;
}
RBT_node* RBT_node::getparent()
{
    return parent;
}
RBT_node* RBT_node::getleft()
{
    return left;
}
RBT_node* RBT_node::getright()
{
    return right;
}
char RBT_node::getcolour()
{
    return colour;
}
void RBT_node::setdata(int value)
{
    data = value;
}
void RBT_node::setleft(RBT_node* ptr)
{
    left = ptr;
}
void RBT_node::setright(RBT_node* ptr)
{
    right = ptr;
}
void RBT_node::setparent(RBT_node* ptr)
{
    parent = ptr;
}
void RBT_node::setcolour(char c)
{
    colour = c;
}
RBT_node::~RBT_node()
{
    return;
}
