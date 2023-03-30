#include "Circular_Queue_ADT.h"
#include <iostream>

using namespace std;

Circular_Queue_ADT::Circular_Queue_ADT(int capacity) : members(capacity+1)
{
    head = 0;
    tail = 0;
}

int Circular_Queue_ADT::successor(int val)
{
    if(val == (members.GetCapacity()-1)) return 0;
    else return (val + 1);
}

bool Circular_Queue_ADT::IsFull()
{
    if(head==successor(tail)) return true;
    else return false;
}

bool Circular_Queue_ADT::IsEmpty()
{
    if(head==tail) return true;
    else return false;
}

bool Circular_Queue_ADT::Add(int value)
{
    if(IsFull()) return false;
    else
    {
        members.SetElement(tail,value);
        tail = successor(tail);
        return true;
    }
}

int Circular_Queue_ADT::Delete()
{
    if(IsEmpty()) return -1;
    else
    {
        int ans = members.GetElement(head);
        head = successor(head);
        return ans;
    }
}

void Circular_Queue_ADT::print_circular_queue()
{
    for(int i=head; i!=tail; i=successor(i))
    {
        if(i!=head) cout<<" ";
        cout<<members.GetElement(i);
    }
    cout<<endl;
}

Circular_Queue_ADT::~Circular_Queue_ADT()
{
    return;
}
