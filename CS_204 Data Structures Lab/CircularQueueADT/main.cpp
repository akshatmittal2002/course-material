#include <iostream>
#include "..\SourceCode\Circular_Queue_ADT.h"

using namespace std;

int main()
{
    int x,val;
    cout<<"ENTER SIZE OF QUEUE: ";
    cin>>x;
    cout<<endl;

    Circular_Queue_ADT cq(x);

    cout<<"Type 1 to ADD elements into circular queue."<<endl;
    cout<<"Type 2 to DELETE elements from circular queue."<<endl;
    cout<<"Type 3 to PRINT the circular queue."<<endl;
    cout<<"Type 4 to QUIT."<<endl;

    while(1)
    {
        cout<<endl;
        cout<<"ENTER: ";
        cin>>x;

        if(x==4) break;
        else if(x==1)
        {
            cout<<"ENTER THE VALUE: ";
            cin>>val;
            if(cq.IsFull()) cout<<"QUEUE IS FULL! CAN NOT ADD "<<val<<"."<<endl;
            else cq.Add(val);
        }
        else if(x==2)
        {
           if(cq.IsEmpty()) cout<<"QUEUE IS EMPTY!"<<endl;
           else cout<<"DELETED ELEMENT: "<<cq.Delete()<<endl;
        }
        else if(x==3)
        {
            cq.print_circular_queue();
        }
        else
        {
            cout<<"Please enter correct number!"<<endl;
        }
    }

    return 0;
}
