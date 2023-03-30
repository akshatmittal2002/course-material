#include "Queue_ADT.h"
#include <iostream>

using namespace std;

Queue_ADT::Queue_ADT(int capacity) : members(capacity)
{
    counter = 0;
}

bool Queue_ADT::IsEmpty()
{
    if(counter==0) return true;
    else return false;
}

bool Queue_ADT::IsFull()
{
    if(counter==members.GetCapacity()) return true;
    else return false;
}

bool Queue_ADT::Add(int value)
{
    if(IsFull())
    {
        return false;
    }
    else
    {
        members.SetElement(counter,value);
        counter++;
        return true;
    }
}

int Queue_ADT::Delete()
{
    if(IsEmpty())
    {
        return -1;
    }
    else
    {
        counter--;
        int ans = members.GetElement(0);
        for(int i=0; i<counter; i++)
        {
            members.SetElement(i,members.GetElement(i+1));
        }
        return ans;
    }
}

void Queue_ADT::print_queue()
{
    for(int i=0; i<counter; i++)
    {
        if(i>0) cout<<" ";
        cout<<members.GetElement(i);
    }
    cout<<endl;
}

Queue_ADT::~Queue_ADT()
{
    return;
}
