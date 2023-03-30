#include "DLL_ADT.h"
#include <iostream>

using namespace std;

DLL_ADT::DLL_ADT()
{
    head = nullptr;
    tail = nullptr;
}

bool DLL_ADT::IsEmpty()
{
    if((head == nullptr) && (tail == nullptr)) return true;
    else return false;
}

void DLL_ADT::AddBeginning(DLL_Node* newnode)
{
    if(IsEmpty())
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        newnode->SetNext(head);
        head->SetPrev(newnode);
        head = newnode;
    }
}

void DLL_ADT::AddEnd(DLL_Node* newnode)
{
    if(IsEmpty())
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        newnode->SetPrev(tail);
        tail->SetNext(newnode);
        tail = newnode;
    }
}

DLL_Node* DLL_ADT::DeleteBeginning()
{
    DLL_Node* ans = nullptr;
    if(IsEmpty());
    else if(head == tail)
    {
        tail = nullptr;
        ans = head;
        head = nullptr;
    }
    else
    {
        ans = head;
        head = head->GetNext();
        head->SetPrev(nullptr);
        ans->SetNext(nullptr);
    }
    return ans;
}

DLL_Node* DLL_ADT::DeleteEnd()
{
    DLL_Node* ans = nullptr;
    if(IsEmpty() || head == tail) ans = DeleteBeginning();
    else
    {
        ans = tail;
        tail = tail->GetPrev();
        tail->SetNext(nullptr);
        ans->SetPrev(nullptr);
    }
    return ans;
}

void DLL_ADT::print_list()
{
    DLL_Node* curr = head;
    cout<<"The List is:";
    while(curr != nullptr)
    {
        cout<<" "<<curr->GetData();
        curr = curr->GetNext();
    }
    cout<<endl;
}

DLL_ADT::~DLL_ADT()
{
    DLL_Node* n;
    while(!IsEmpty())
    {
        n = DeleteBeginning();
        delete n;
    }
    return;
}
