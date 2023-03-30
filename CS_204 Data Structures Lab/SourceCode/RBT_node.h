#ifndef RBT_NODE_H
#define RBT_NODE_H
#include <iostream>
using namespace std;

class RBT_node
{
    public:
        RBT_node(int);
        virtual ~RBT_node();
        int getdata();
        RBT_node* getparent();
        RBT_node* getleft();
        RBT_node* getright();
        char getcolour();
        void setdata(int);
        void setleft(RBT_node*);
        void setright(RBT_node*);
        void setparent(RBT_node*);
        void setcolour(char);

    protected:

    private:
        int data;
        RBT_node* left;
        RBT_node* right;
        RBT_node* parent;
        char colour;
};

#endif
