#include <iostream>
#include "..\SourceCode\Stack_ADT.h"

using namespace std;

int main()
{
    int x,val;
    cout<<"ENTER SIZE OF STACK: ";
    cin>>x;
    cout<<endl;

    Stack_ADT s(x);

    cout<<"Type 1 to PUSH elements into stack."<<endl;
    cout<<"Type 2 to POP elements from stack."<<endl;
    cout<<"Type 3 to PRINT the stack."<<endl;
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
            if(s.IsFull()) cout<<"STACK IS FULL! CAN NOT ADD "<<val<<"."<<endl;
            else s.push(val);
        }
        else if(x==2)
        {
            if(s.IsEmpty()) cout<<"STACK IS EMPTY!"<<endl;
            else cout<<"POPPED ELEMENT: "<<s.pop()<<endl;
        }
        else if(x==3)
        {
            s.print_stack();
        }
        else
        {
            cout<<"Please enter correct number!"<<endl;
        }
    }

    return 0;
}
