#include "DLL_Node.h"

DLL_Node::DLL_Node(int value)
{
    data = value;
    next = nullptr;
    prev = nullptr;
}

int DLL_Node::GetData()
{
    return data;
}

DLL_Node* DLL_Node::GetNext()
{
    return next;
}

DLL_Node* DLL_Node::GetPrev()
{
    return prev;
}

void DLL_Node::SetNext(DLL_Node* ptr)
{
    next = ptr;
}

void DLL_Node::SetPrev(DLL_Node* ptr)
{
    prev = ptr;
}

DLL_Node::~DLL_Node()
{
    return;
}
