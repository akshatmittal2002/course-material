#include "Stack_ADT.h"
#include <iostream>

using namespace std;

Stack_ADT::Stack_ADT(int capacity): members(capacity)
{
    ///Creates a stack of particular capacity.
    counter = 0;
}

bool Stack_ADT::IsEmpty()
{
    ///Checks if our stack is empty or not.
    if(counter==0) return true;
    else return false;
}

bool Stack_ADT::IsFull()
{
    ///Checks if our stack is full or not.
    if(counter==members.GetCapacity()) return true;
    else return false;
}

bool Stack_ADT::push(int val)
{
   ///Insert an element at top of the stack.
   if(IsFull())
   {
       return false;
   }
   else
   {
       members.SetElement(counter,val);
       counter++;
       return true;
   }
}

int Stack_ADT::pop()
{
    ///Removes the top element of stack.
    if(IsEmpty())
    {
        return -1;
    }
    else
    {
        counter--;
        return members.GetElement(counter);
    }
}

void Stack_ADT::print_stack()
{
    for(int i=0; i<counter; i++)
    {
        if(i>0) cout<<" ";
        cout<<members.GetElement(i);
    }
    cout<<endl;
}

Stack_ADT::~Stack_ADT()
{
    return;
}
