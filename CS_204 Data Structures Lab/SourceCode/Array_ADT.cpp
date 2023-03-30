#include "Array_ADT.h"

Array_ADT::Array_ADT()
{
    capacity = 0;
    elements = nullptr;
}

Array_ADT::Array_ADT(int arraysize)
{
    capacity = arraysize;
    elements = new int[arraysize];
}

void Array_ADT::SetElement(int index,int value)
{
    elements[index] = value;
}

int Array_ADT::GetElement(int index)
{
    return (elements[index]);
}

int Array_ADT::GetCapacity()
{
    return capacity;
}

Array_ADT::~Array_ADT()
{
    delete[] elements;
    return;
}
