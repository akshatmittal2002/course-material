#include <iostream>
#include "..\SourceCode\Queue_ADT.h"

using namespace std;

int main()
{
    int x,val;
    cout<<"ENTER SIZE OF QUEUE: ";
    cin>>x;
    cout<<endl;

    Queue_ADT q(x);

    cout<<"Type 1 to ADD elements into queue."<<endl;
    cout<<"Type 2 to DELETE elements from queue."<<endl;
    cout<<"Type 3 to PRINT the queue."<<endl;
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
            if(q.IsFull()) cout<<"QUEUE IS FULL! CAN NOT ADD "<<val<<"."<<endl;
            else q.Add(val);
        }
        else if(x==2)
        {
           if(q.IsEmpty()) cout<<"QUEUE IS EMPTY!"<<endl;
           else cout<<"DELETED ELEMENT: "<<q.Delete()<<endl;
        }
        else if(x==3)
        {
            q.print_queue();
        }
        else
        {
            cout<<"Please enter correct number!"<<endl;
        }
    }

    return 0;
}
