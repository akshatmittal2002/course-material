#include "RBT.h"

RBT::RBT()
{
    nil = new RBT_node(-1);
    nil->setcolour('b');
    root = nullptr;
}
RBT_node* RBT::search_subtree(int value,RBT_node* tree)
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
        return search_subtree(value,tree->getleft());
    }
    else
    {
        return search_subtree(value,tree->getright());
    }
}
RBT_node* RBT::search_tree(int value)
{
    return search_subtree(value,root);
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
    RBT_node* node = search_subtree(value,root);
    if(node==nullptr) return 'n';
    return (node->getcolour());
}
int RBT::get_root()
{
    if(root==nullptr) return -1;
    return (root->getdata());
}
RBT_node* RBT::minimum(RBT_node* tree)
{
    RBT_node* curr = tree;
    while(curr->getleft() != nil)
    {
        curr = curr->getleft();
    }
    return curr;
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
}
void RBT::transplant(RBT_node* u, RBT_node* v)
{
    if(u->getparent()==nil) root = v;
    else if(u == (u->getparent())->getleft()) (u->getparent())->setleft(v);
    else (u->getparent())->setright(v);
    v->setparent(u->getparent());
}
RBT_node* RBT::delete_node(int value)
{
    RBT_node* z = search_subtree(value,root);
    if(z==nullptr)
    {
        return nullptr;
    }
    RBT_node* y = z;
    char y_colour = y->getcolour();
    RBT_node* x = nullptr;
    if(z->getright()==nil)
    {
        x = z->getleft();
        transplant(z,x);
    }
    else if(z->getleft()==nil)
    {
        x = z->getright();
        transplant(z,x);
    }
    else
    {
        y = minimum(z->getright());
        y_colour = y->getcolour();
        x = y->getright();
        if(y->getparent()!=z)
        {
            transplant(y,x);
            y->setright(z->getright());
            (y->getright())->setparent(y);
        }
        else
        {
            x->setparent(y);
        }
        transplant(z,y);
        y->setleft(z->getleft());
        (y->getleft())->setparent(y);
        y->setcolour(z->getcolour());
    }
    if(y_colour=='b')
    {
        while((x!=root)&&(x->getcolour()=='b'))
        {
            RBT_node* x_par = x->getparent();
            RBT_node* w = nullptr;
            if(x==x_par->getright
               ())
            {
                w = x_par->getleft();
                if(w->getcolour()=='r')
                {
                    w->setcolour('b');
                    x_par->setcolour('r');
                    right_rotation(x_par);
                    w = x_par->getleft();
                }
                if((w->getright())->getcolour()=='b' && (w->getleft())->getcolour()=='b')
                {
                    w->setcolour('r');
                    x = x_par;
                }
                else
                {
                    if((w->getleft())->getcolour()=='b')
                    {
                        (w->getright())->setcolour('b');
                        w->setcolour('b');
                        left_rotation(w);
                        w = x_par->getleft();
                    }
                    w->setcolour(x_par->getcolour());
                    x_par->setcolour('b');
                    (w->getleft())->setcolour('b');
                    right_rotation(x_par);
                    x=root;
                }
            }
            else
            {
                w = x_par->getright();
                if(w->getcolour()=='r')
                {
                    w->setcolour('b');
                    x_par->setcolour('r');
                    left_rotation(x_par);
                    w = x_par->getright();
                }
                if((w->getleft())->getcolour()=='b' && (w->getright())->getcolour()=='b')
                {
                    w->setcolour('r');
                    x = x_par;
                }
                else
                {
                    if((w->getright())->getcolour()=='b')
                    {
                        (w->getleft())->setcolour('b');
                        w->setcolour('b');
                        right_rotation(w);
                        w = x_par->getright();
                    }
                    w->setcolour(x_par->getcolour());
                    x_par->setcolour('b');
                    (w->getright())->setcolour('b');
                    left_rotation(x_par);
                    x=root;
                }
            }
        }
        x->setcolour('b');
    }
    z->setparent(nullptr);
    z->setright(nullptr);
    z->setleft(nullptr);
    return z;
}
RBT::~RBT()
{
    return;
}
