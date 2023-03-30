#include <iostream>
using namespace std;
///Declaration of a class that will define our node of a tree.
class BST_node
{
    public:
        BST_node(int); //Constructor
        virtual ~BST_node(); //Destructor
        void setdata(int); //Set data of node.
        void setleft(BST_node*); //Set left child of node.
        void setright(BST_node*); //Set right child of node.
        void setparent(BST_node*); //Set parent of node.
        int getdata(); //Return data of node.
        BST_node* getleft(); //Return address of left child of node.
        BST_node* getright(); //Return address of right child of node.
        BST_node* getparent(); //Return address of parent of node.

    private:
        int data; //Store data of node
        BST_node* left; //Store address of left child.
        BST_node* right; //Store address of right child.
        BST_node* parent; //Store address of parent.
};
///Declaration of a class that will define our tree.
///================================================================================================
class BST
{
    public:
        BST(); //Constructor
        virtual ~BST(); //Destructor
        void add_node(BST_node*); //Function to add a new node in tree.
        BST_node* search_tree(int); //Function to search for a value inside tree.
        int height_tree(); //Function to find height of tree.
        int num_nodes(int); //Function to find number of nodes in a subtree.
        int common(int,int); //Function to find smallest common ancestor.

    protected:

    private:
        BST_node* root; //Store the address of root node of tree.
        BST_node* search_subtree(int,BST_node*); //Search a value inside a subtree.
        int height_subtree(BST_node*); //Find height of a subtree.
        int num_nodes_subtree(BST_node*); //Find number of nodes inside a subtree.
};
///I am assuming all numbers that are to be added into tree will be distinct.
///================================================================================================
int main()
{
    //Required variables to take input.
    int num_of_nums=0,num=0,num_1=0,num_2=0,num_3=0;
    //Take input of number of nodes to be added.
    cin>>num_of_nums;
    //Declare a new node.
    BST_node* new_node;
    //Declare a new tree.
    BST tree;
    //Take input of all nodes and add them in given order.
    for(int i=0; i<num_of_nums; i++)
    {
        cin>>num;
        //Create a new node with given value whose address will be stored in our variable.
        new_node = new BST_node(num);
        //Attach the node in our tree.
        tree.add_node(new_node);
    }
    //Take remaining input.
    cin>>num_1>>num_2>>num_3;
    //Find height of tree, common ancestor and number of nodes and print them accordingly.
    cout<<tree.height_tree()<<" "<<tree.common(num_1,num_2)<<" "<<tree.num_nodes(num_3)<<"\n";
}
///================================================================================================
///Function Definition of various functions in BST node class.
BST_node::BST_node(int value)
{
    //Constructor will set data to given value and all three addresses to NULL.
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
}
///================================================================================================
///Function Definition of various functions in BST class.
BST::BST()
{
    //Constructor will set root to NULL.
    root = nullptr;
}
void BST::add_node(BST_node* newnode)
{
    if(root==nullptr)
    {
        root = newnode;
        return;
    }
    BST_node* curr = root;
    while(1)
    {
        if(newnode->getdata() > curr->getdata())
        {
            if(curr->getright()!=nullptr)
            {
                curr = curr->getright();
            }
            else
            {
                curr->setright(newnode);
                newnode->setparent(curr);
                return;
            }
        }
        else
        {
            if(curr->getleft()!=nullptr)
            {
                curr = curr->getleft();
            }
            else
            {
                curr->setleft(newnode);
                newnode->setparent(curr);
                return;
            }
        }
    }
}
BST_node* BST::search_tree(int value)
{
    return search_subtree(value,root);
}
BST_node* BST::search_subtree(int value,BST_node* tree)
{
    if(tree==nullptr)
    {
        return nullptr;
    }
    if(value==tree->getdata())
    {
        return tree;
    }
    if(value < tree->getdata())
    {
        return search_subtree(value,tree->getleft());
    }
    else
    {
        return search_subtree(value,tree->getright());
    }
}
int BST::height_tree()
{
    //Return height of subtree which is starting at root.
    return height_subtree(root);
}
int BST::height_subtree(BST_node* tree)
{
    //If given tree is NULL, its height is zero.
    if(tree==nullptr)
    {
        return 0;
    }
    //Calculate height of left and right subtree of given tree.
    int left = height_subtree(tree->getleft());
    int right = height_subtree(tree->getright());
    //Height of tree will be maximum of height of both the subtrees.
    //Done plus 1 to count the root node as well.
    return (max(left,right) + 1);
}
int BST::num_nodes(int value)
{
    //Search for node with given value.
    BST_node* tree = search_tree(value);
    //Return number of nodes in given subtree.
    return num_nodes_subtree(tree);
}
int BST::num_nodes_subtree(BST_node* tree)
{
    //If tree is NULL, number of nodes is zero.
    if(tree==nullptr)
    {
        return 0;
    }
    //Calculate number of nodes in left subtree as well as right subtree.
    int left_nodes = num_nodes_subtree(tree->getleft());
    int right_nodes = num_nodes_subtree(tree->getright());
    //Number of nodes in given tree will be sum of nodes in both subtrees.
    //Done plus 1 to count the root node.
    return (left_nodes + right_nodes + 1);
}
int BST::common(int value1, int value2)
{
    //Search for both the numbers in given tree.
    BST_node* node1 = search_tree(value1);
    BST_node* node2 = search_tree(value2);
    //If root of tree is NULL or any of the two nodes does not exist in tree, return 0.
    if(root==nullptr || node1==nullptr || node2==nullptr)
    {
        return 0;
    }
    //Current points to root initially.
    BST_node* curr = root;
    //Start an infinite loop
    while(1)
    {
        //If current node is NULL, return 0.
        if(curr==nullptr)
        {
            return 0;
        }
        //Get the data of current node.
        int data = curr->getdata();
        //If both values are greater than data of current node, then the least ancestor exists in right subtree of given subtree.
        if(value1 > data && value2 > data)
        {
            curr = curr->getright();
        }
        //Similarly, if both values are less than data of current node, then the least ancestor exists in left subtree of given subtree.
        else if(value1 < data && value2 < data)
        {
            curr = curr->getleft();
        }
        /*In all other conditions, i.e.,
        1. Value 1 is less than current node and value 2 is greater than current node or vice-versa.
        2. Either value 1 or value 2 or both are equal to current node.
        Least ancestor of given two nodes is current node.*/
        else
        {
            return data;
        }
    }
}
BST::~BST()
{
}
