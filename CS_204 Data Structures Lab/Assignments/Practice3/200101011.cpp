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

    protected:

    private:
        RBT_node* root;
        RBT_node* nil;
        RBT_node* search_inside(int,RBT_node*);
        void left_rotation(RBT_node*);
        void right_rotation(RBT_node*);
        void inorder_inside(RBT_node*);
        int height_subtree(RBT_node*);
};
int main()
{
    RBT tree;
    RBT_node* n;
    int code,value;
    cout<<"Type 1 to add a node in tree.\n";
    cout<<"Type 2 to search a value in tree.\n";
    cout<<"Type 3 to print the tree in in-order.\n";
    cout<<"Type 4 to get root of tree.\n";
    cout<<"Type 5 to get height of the tree.\n";
    cout<<"Type 6 to get colour of a node.\n";
    cout<<"Type 7 to quit.\n";
    while(1)
    {
        cout<<"\nENTER CODE: ";
        cin>>code;
        if(code==1)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = new RBT_node(value);
            tree.add_node(n);
        }
        else if(code==2)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            if(tree.search_tree(value)) cout<<"YES\n";
            else cout<<"NO\n";
        }
        else if(code==3)
        {
            cout<<"TREE DATA: ";
            tree.print_inorder();
        }
        else if(code==4)
        {
            cout<<"ROOT: "<<tree.get_root()<<"\n";
        }
        else if(code==5)
        {
            cout<<"HEIGHT: "<<tree.height()<<"\n";
        }
        else if(code==6)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            if(tree.colour(value)=='b') cout<<"COLOUR: Black\n";
            else if(tree.colour(value)=='r') cout<<"COLOUR: Red\n";
            else cout<<value<<" is not present in tree.\n";
        }
        else if(code==7)
        {
            break;
        }
        else
        {
            cout<<"INVALID CODE\n";
        }
    }
    return 0;
}
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
RBT::RBT()
{
    nil = new RBT_node(-1);
    nil->setcolour('b');
    root = nullptr;
}
RBT_node* RBT::search_inside(int value,RBT_node* tree)
{
    if(tree==nil)
    {
        return nullptr;
    }
    else if(value==tree->getdata())
    {
        return tree;
    }
    else if(value<tree->getdata())
    {
        return search_inside(value,tree->getleft());
    }
    else
    {
        return search_inside(value,tree->getright());
    }
}
RBT_node* RBT::search_tree(int value)
{
    return search_inside(value,root);
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
        if(par==grandpar->getleft())
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
        else
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
    }
    root->setcolour('b');
}
void RBT::inorder_inside(RBT_node* tree)
{
    if(tree==nil)
    {
        return;
    }
    inorder_inside(tree->getleft());
    cout<<tree->getdata()<<" ";
    inorder_inside(tree->getright());
}
void RBT::print_inorder()
{
    inorder_inside(root);
    cout<<"\n";
}
int RBT::height()
{
    return height_subtree(root);
}
int RBT::height_subtree(RBT_node* tree)
{
    if(tree==nil || tree==nullptr)
    {
        return 0;
    }
    int left = height_subtree(tree->getleft());
    int right = height_subtree(tree->getright());
    return (max(left,right) + 1);
}
char RBT::colour(int value)
{
    RBT_node* node = search_inside(value,root);
    if(node==nullptr) return 'n';
    return (node->getcolour());
}
int RBT::get_root()
{
    if(root==nullptr) return -1;
    return (root->getdata());
}
RBT::~RBT()
{
    return;
}
