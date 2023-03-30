#include "BST.h"

BST::BST()
{
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
        if(newnode->getdata() <= curr->getdata())
        {
            if(curr->getleft()==nullptr)
            {
                curr->setleft(newnode);
                newnode->setparent(curr);
                return;
            }
            else
            {
                curr = curr->getleft();
            }
        }
        else
        {
            if(curr->getright()==nullptr)
            {
                curr->setright(newnode);
                newnode->setparent(curr);
                return;
            }
            else
            {
                curr = curr->getright();
            }
        }
    }
}
BST_node* BST::search_inside(int value,BST_node* tree)
{
    if(tree==nullptr)
    {
        return nullptr;
    }
    if(value==tree->getdata())
    {
        return tree;
    }
    if(value<tree->getdata())
    {
        return search_inside(value,tree->getleft());
    }
    else
    {
        return search_inside(value,tree->getright());
    }
}
void BST::inorder_inside(BST_node* tree)
{
    if(tree==nullptr)
    {
        return;
    }
    inorder_inside(tree->getleft());
    cout<<tree->getdata()<<" ";
    inorder_inside(tree->getright());
}
void BST::preorder_inside(BST_node* tree)
{
    if(tree==nullptr)
    {
        return;
    }
    cout<<tree->getdata()<<" ";
    preorder_inside(tree->getleft());
    preorder_inside(tree->getright());
}
void BST::postorder_inside(BST_node* tree)
{
    if(tree==nullptr)
    {
        return;
    }
    postorder_inside(tree->getleft());
    postorder_inside(tree->getright());
    cout<<tree->getdata()<<" ";
}
BST_node* BST::minimum_inside(BST_node* tree)
{
    BST_node* curr = tree;
    while(curr->getleft())
    {
        curr = curr->getleft();
    }
    return curr;
}
BST_node* BST::maximum_inside(BST_node* tree)
{
    BST_node* curr = tree;
    while(curr->getright())
    {
        curr = curr->getright();
    }
    return curr;
}
BST_node* BST::succ_inside(int value,BST_node* node)
{
    if(node==nullptr)
    {
        return nullptr;
    }
    BST_node* curr = node;
    BST_node* ans = nullptr;
    while(curr)
    {
        if(curr->getdata() == value)
        {
            if(curr->getright())
            {
                ans = minimum_inside(curr->getright());
            }
            break;
        }
        else if(curr->getdata() > value)
        {
            ans = curr;
            curr = curr->getleft();
        }
        else
        {
            curr = curr->getright();
        }
    }
    return ans;
}
BST_node* BST::pred_inside(int value,BST_node* node)
{
    if(node==nullptr)
    {
        return nullptr;
    }
    BST_node* curr = node;
    BST_node* ans = nullptr;
    while(curr)
    {
        if(curr->getdata() == value)
        {
            if(curr->getleft())
            {
                ans = maximum_inside(curr->getleft());
            }
            break;
        }
        else if(curr->getdata() > value)
        {
            curr = curr->getleft();
        }
        else
        {
            ans = curr;
            curr = curr->getright();
        }
    }
    return ans;
}
BST_node* BST::search_tree(int value)
{
    return search_inside(value,root);
}
BST_node* BST::succ(int value)
{
    return succ_inside(value,root);
}
BST_node* BST::pred(int value)
{
    return pred_inside(value,root);
}
BST_node* BST::minimum()
{
    return minimum_inside(root);
}
BST_node* BST::maximum()
{
    return maximum_inside(root);
}
void BST::print_inorder()
{
    inorder_inside(root);
    cout<<endl;
}
void BST::print_preorder()
{
    preorder_inside(root);
    cout<<endl;
}
void BST::print_postorder()
{
    postorder_inside(root);
    cout<<endl;
}
int BST::height()
{
    return height_subtree(root);
}
int BST::height_subtree(BST_node* tree)
{
    if(tree==nullptr)
    {
        return 0;
    }
    int left = height_subtree(tree->getleft());
    int right = height_subtree(tree->getright());
    return (max(left,right) + 1);
}
BST_node* BST::delete_node(int value)
{
    BST_node* ans = search_inside(value,root);
    if(ans==nullptr)
    {
        return nullptr;
    }
    if(ans->getleft()!=nullptr && ans->getright()!=nullptr)
    {
        BST_node* suc = succ_inside(ans->getdata(),ans);
        ans->setdata(suc->getdata());
        ans = suc;
    }
    BST_node* par = ans->getparent();
    ans->setparent(nullptr);
    if(ans->getleft()==nullptr && ans->getright()==nullptr)
    {
        if(ans==root)
        {
            root=nullptr;
        }
        else
        {
            if(par->getleft()==ans) par->setleft(nullptr);
            else par->setright(nullptr);
        }
    }
    else
    {
        if(ans==root)
        {
            if(root->getleft())
            {
                root=root->getleft();
                ans->setleft(nullptr);
            }
            else
            {
                root=root->getright();
                ans->setright(nullptr);
            }
            root->setparent(nullptr);
        }
        else
        {
            if(par->getleft()==ans)
            {
                if(ans->getleft())
                {
                    par->setleft(ans->getleft());
                    (ans->getleft())->setparent(par);
                    ans->setleft(nullptr);
                }
                else
                {
                    par->setleft(ans->getright());
                    (ans->getright())->setparent(par);
                    ans->setright(nullptr);
                }
            }
            else
            {
                if(ans->getleft())
                {
                    par->setright(ans->getleft());
                    (ans->getleft())->setparent(par);
                    ans->setleft(nullptr);
                }
                else
                {
                    par->setright(ans->getright());
                    (ans->getright())->setparent(par);
                    ans->setright(nullptr);
                }
            }
        }
    }
    return ans;
}
BST::~BST()
{
    return;
}
