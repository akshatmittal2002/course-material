#include <iostream>
#include "..\SourceCode\Array_ADT.h"

using namespace std;

int main()
{
    int x,index,value;
    cout<<"ENTER SIZE OF ARRAY: ";
    cin>>x;
    cout<<endl;

    Array_ADT a(x);

    cout<<"Type 1 to SET an element of array. By default elements are set to '0'."<<endl;
    cout<<"Type 2 to GET an element of array."<<endl;
    cout<<"Type 3 to PRINT the full array."<<endl;
    cout<<"Type 4 to QUIT."<<endl;

    for(int i=0; i<x; i++)
    {
        a.SetElement(i,0);
    }

    while(1)
    {
        cout<<endl;
        cout<<"ENTER: ";
        cin>>x;
        if(x==4) break;
        else if(x==1)
        {
            cout<<"ENTER THE INDEX(1-"<<a.GetCapacity()<<"): ";
            cin>>index;
            while(index<1 || index>a.GetCapacity())
            {
                cout<<"Please give correct index! Re-Enter: ";
                cin>>index;
            }
            cout<<"ENTER THE VALUE: ";
            cin>>value;
            a.SetElement(index-1,value);
        }
        else if(x==2)
        {
            cout<<"ENTER THE INDEX(1-"<<a.GetCapacity()<<"): ";
            cin>>index;
            while(index<1 || index>a.GetCapacity())
            {
                cout<<"Please give correct index! Re-Enter: ";
                cin>>index;
            }
            cout<<a.GetElement(index-1)<<endl;
        }
        else if(x==3)
        {
            for(int i=0; i<a.GetCapacity(); i++)
            {
                cout<<a.GetElement(i);
                if(i<a.GetCapacity()-1) cout<<" ";
            }
            cout<<endl;
        }
        else
        {
            cout<<"Please enter correct number!"<<endl;
        }
    }
    return 0;
}
