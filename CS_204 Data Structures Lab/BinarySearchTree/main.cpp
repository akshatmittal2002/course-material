#include <iostream>
#include "../SourceCode/BST.h"
using namespace std;

int main()
{
    BST tree;
    BST_node* n;
    int code,value;
    cout<<"Type 1 to add a node in tree.\n";
    cout<<"Type 2 to search a value in tree.\n";
    cout<<"Type 3 to get minimum value in tree.\n";
    cout<<"Type 4 to get maximum value in tree.\n";
    cout<<"Type 5 to get successor of an element in tree.\n";
    cout<<"Type 6 to get predecessor of an element in tree.\n";
    cout<<"Type 7 to print the tree in in-order.\n";
    cout<<"Type 8 to print the tree in pre-order.\n";
    cout<<"Type 9 to print the tree in post-order.\n";
    cout<<"Type 10 to get height of tree.\n";
    cout<<"Type 11 to delete a node from tree.\n";
    cout<<"Type 12 to quit.\n";
    while(1)
    {
        cout<<"\nENTER CODE: ";
        cin>>code;
        if(code==1)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = new BST_node(value);
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
            cout<<"MINIMUM: "<<tree.minimum()->getdata()<<endl;
        }
        else if(code==4)
        {
            cout<<"MAXIMUM: "<<tree.maximum()->getdata()<<endl;
        }
        else if(code==5 || code==6)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            if(code==5)
            {
                n = tree.succ(value);
                if(n==nullptr) cout<<tree.maximum()->getdata()<<" is the largest element in tree.\nCould not find successor of "<<value<<endl;
                else cout<<"Successor of "<<value<<" in tree: "<<n->getdata()<<endl;
            }
            else
            {
                n = tree.pred(value);
                if(n==nullptr) cout<<tree.minimum()->getdata()<<" is the smallest element in tree.\nCould not find predecessor of "<<value<<endl;
                else cout<<"Predecessor of "<<value<<" in tree: "<<n->getdata()<<endl;
            }
        }
        else if(code==7)
        {
            cout<<"TREE DATA: ";
            tree.print_inorder();
        }
        else if(code==8)
        {
            cout<<"TREE DATA: ";
            tree.print_preorder();
        }
        else if(code==9)
        {
            cout<<"TREE DATA: ";
            tree.print_postorder();
        }
        else if(code==10)
        {
            cout<<"Height = "<<tree.height()<<"\n";
        }
        else if(code==11)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = tree.delete_node(value);
            if(n==nullptr) cout<<value<<" is not present in tree.\n";
            else cout<<"Deleted "<<value<<" successfully.\n";
        }
        else if(code==12)
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
