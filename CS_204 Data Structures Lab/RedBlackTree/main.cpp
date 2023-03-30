#include <iostream>
#include "../SourceCode/RBT.h"
using namespace std;

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
    cout<<"Type 9 to delete a node from tree.\n";
    cout<<"Type 8 to quit.\n";
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
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = tree.delete_node(value);
            if(n==nullptr) cout<<value<<" is not present in tree.\n";
            else cout<<value<<" deleted successfully\n";
            free(n);
        }
        else if(code==8)
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
