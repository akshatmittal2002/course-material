#include "SLL_Node.h"

SLL_Node::SLL_Node(int value)
{
    data = value;
    next = nullptr;
}

int SLL_Node::GetData()
{
    return data;
}

SLL_Node* SLL_Node::GetNext()
{
    return next;
}

void SLL_Node::SetNext(SLL_Node* nextptr)
{
    next = nextptr;
}

SLL_Node::~SLL_Node()
{
    return;
}
