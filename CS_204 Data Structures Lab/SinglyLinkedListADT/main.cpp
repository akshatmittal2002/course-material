#include <iostream>
#include "..\SourceCode\SLL_ADT.h"

using namespace std;

int main()
{
    int x,value;
    SLL_ADT l;
    SLL_Node* n;
    cout<<"Type 1 to add a new item at beginning of the list."<<endl;
    cout<<"Type 2 to add a new item at end of the list."<<endl;
    cout<<"Type 3 to delete an item from beginning of the list."<<endl;
    cout<<"Type 4 to delete an item from end of the list."<<endl;
    cout<<"Type 5 to print the list."<<endl;
    cout<<"Type 6 to exit."<<endl;

    while(1)
    {
        cout<<endl<<"ENTER: ";
        cin>>x;
        if(x==1 || x==2)
        {
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = new SLL_Node(value);
            if(x==1) l.AddBeginning(n);
            else l.AddEnd(n);
        }
        else if(x==3)
        {
            n = l.DeleteBeginning();
            if(n == nullptr) cout<<"List Is Empty!"<<endl;
            else cout<<"Deleted Item Is: "<<n->GetData()<<endl;
            delete n;
        }
        else if(x==4)
        {
            n = l.DeleteEnd();
            if(n == nullptr) cout<<"List Is Empty!"<<endl;
            else cout<<"Deleted Item Is: "<<n->GetData()<<endl;
            delete n;
        }
        else if(x==5)
        {
            l.print_list();
        }
        else if(x==6) break;
        else
        {
            cout<<"Please enter correct number!"<<endl;
        }
    }
    return 0;
}
