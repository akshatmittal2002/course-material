#include <iostream>
using namespace std;
///=======================================================================
///Declaration of a class that will define our node of a tree.
class RBT_node
{
    public:
        RBT_node(int); //Constructor
        virtual ~RBT_node(); //Destructor
        int getdata(); //Return data of node.
        RBT_node* getparent(); //Return address of parent of node.
        RBT_node* getleft(); //Return address of left child of node.
        RBT_node* getright(); //Return address of right child of node.
        char getcolour(); //Return color of node.
        void setleft(RBT_node*); //Set left child of node.
        void setright(RBT_node*); //Set right child of node.
        void setparent(RBT_node*); //Set parent of node.
        void setcolour(char); //Set colour of node.
    private:
        int data; //Store data of node
        RBT_node* left; //Store address of left child.
        RBT_node* right; //Store address of right child.
        RBT_node* parent; //Store address of parent.
        char colour; //Store colour of node.
};
///=======================================================================
///Declaration of a class that will define our tree.
class RBT
{
    public:
        RBT(); //Constructor
        virtual ~RBT(); //Destructor
        void add_node(RBT_node*); //Function to add a new node in tree.
        void get_preorder(int*); //Function to find required permutation of tree nodes, i.e., just pre-order traversal of tree.
    private:
        RBT_node* root; //Store the address of root node of tree.
        RBT_node* nil; //Store the address of NIL node of tree.
        void left_rotation(RBT_node*); //Function to perform a left rotation about a node.
        void right_rotation(RBT_node*); //Function to perform a right rotation about a node.
        void preorder_inside(RBT_node*,int*,int*); //Function for recursive call inside pre-order traversal.
};
///=======================================================================
int main()
{
    //Required variable to take input of total numbers to be added.
    int total_num;
    //Take input.
    cin>>total_num;
    //Declare a new tree.
    RBT tree;
    //Declare a new node.
    RBT_node* node;
    //Required variable to take input of a number to be added.
    int num;
    //Take input of all nodes and add them in given order.
    for(int i=0; i<total_num; i++)
    {
        //Take input of first number.
        cin>>num;
        //Create a new node with given value whose address will be stored in our variable.
        node = new RBT_node(num);
        //Attach the node in our tree.
        tree.add_node(node);
    }
    //Declare an array to store the numbers in tree.
    int permutation[total_num];
    //Use pre-order traversal of tree to store numbers of tree and get required permutation.
    tree.get_preorder(permutation);
    //Print the permutation array.
    for(int i=0; i<total_num; i++)
    {
        if(i!=0) cout<<" ";
        cout<<permutation[i];
    }
    //Add a newline at end.
    cout<<"\n";
}
///=======================================================================
///Function Definition of various functions in RBT node class.
RBT_node::RBT_node(int value)
{
    //Constructor will set data to given value, all three addresses to NULL ans colour to red.
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
RBT_node::~RBT_node(){
}
///=======================================================================
///Function Definition of various functions in RBT class.
RBT::RBT()
{
    //Constructor will set root to NULL and create the rectangular leaf of black colour, i.e., NIL.
    nil = new RBT_node(-1);
    nil->setcolour('b');
    root = nullptr;
}
void RBT::preorder_inside(RBT_node* tree, int* arr, int* curr)
{
    //Recursively traverse the tree.
    //If tree is black rectangular leaf, then return from the function.
    if(tree==nil)
    {
        return;
    }
    //Add root of current subtree to given index of array.
    arr[*curr] = tree->getdata();
    //Increment index by one.
    //I am using call be reference instead of call by value which will make changes in current variable all across and we don't have to worry.
    //Remember to de-reference, since current is an address.
    (*curr)++;
    //Call pre-order traversal for left subtree.
    preorder_inside(tree->getleft(),arr,curr);
    //Then call pre-order traversal for right subtree.
    preorder_inside(tree->getright(),arr,curr);
}
void RBT::get_preorder(int* arr)
{
    //Pre-order traversal of tree starts from root.
    //Initialize current index to zero
    int curr = 0;
    //Pass the array and address of current to recursive function.
    preorder_inside(root,arr,&curr);
}
void RBT::left_rotation(RBT_node* node)
{
    RBT_node* par = node->getparent();
    RBT_node* alpha = node->getright();
    RBT_node* beta = alpha->getleft();
    alpha->setleft(node);
    node->setparent(alpha);
    node->setright(beta);
    beta->setparent(node);
    alpha->setparent(par);
    if(par==nil)
    {
        root=alpha;
    }
    else
    {
        if(par->getleft()==node) par->setleft(alpha);
        else par->setright(alpha);
    }
}
void RBT::right_rotation(RBT_node* node)
{
    RBT_node* par = node->getparent();
    RBT_node* alpha = node->getleft();
    RBT_node* beta = alpha->getright();
    alpha->setright(node);
    node->setparent(alpha);
    node->setleft(beta);
    beta->setparent(node);
    alpha->setparent(par);
    if(par==nil)
    {
        root=alpha;
    }
    else
    {
        if(par->getleft()==node) par->setleft(alpha);
        else par->setright(alpha);
    }
}
void RBT::add_node(RBT_node* node)
{
    node->setright(nil);
    node->setleft(nil);
    node->setparent(nil);
    if(root==nullptr)
    {
        root = node;
        root->setcolour('b');
        return;
    }
    RBT_node* curr = root;
    RBT_node* par = curr;
    while(curr!=nil)
    {
        par = curr;
        if(node->getdata() <= curr->getdata()) curr=curr->getleft();
        else curr=curr->getright();
    }
    node->setparent(par);
    if(node->getdata() <= par->getdata()) par->setleft(node);
    else par->setright(node);
    curr = node;
    while((curr->getparent())->getcolour() == 'r')
    {
        par = curr->getparent();
        RBT_node* grandpar = par->getparent();
        RBT_node* uncle = grandpar;
        if(par==grandpar->getright())
        {
            uncle = grandpar->getleft();
            if(uncle->getcolour()=='r')
            {
                par->setcolour('b');
                grandpar->setcolour('r');
                uncle->setcolour('b');
                curr = grandpar;
            }
            else
            {
                if(curr==par->getleft())
                {
                    right_rotation(par);
                    curr = par;
                    par = curr->getparent();
                }
                par->setcolour('b');
                grandpar->setcolour('r');
                left_rotation(grandpar);
            }
        }
        else
        {
            uncle = grandpar->getright();
            if(uncle->getcolour()=='r')
            {
                par->setcolour('b');
                grandpar->setcolour('r');
                uncle->setcolour('b');
                curr = grandpar;
            }
            else
            {
                if(curr==par->getright())
                {
                    left_rotation(par);
                    curr = par;
                    par = curr->getparent();
                }
                par->setcolour('b');
                grandpar->setcolour('r');
                right_rotation(grandpar);
            }
        }
    }
    root->setcolour('b');
    return;
}
RBT::~RBT(){
}
