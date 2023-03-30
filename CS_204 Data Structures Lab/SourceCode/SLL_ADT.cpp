#include "SLL_ADT.h"
#include <iostream>

using namespace std;

SLL_ADT::SLL_ADT()
{
    head = nullptr;
}

bool SLL_ADT::IsEmpty()
{
    if(head == nullptr) return true;
    else return false;
}

void SLL_ADT::AddBeginning(SLL_Node* newnode)
{
    newnode->SetNext(head);
    head = newnode;
}

void SLL_ADT::AddEnd(SLL_Node* newnode)
{
    newnode->SetNext(nullptr);
    SLL_Node* curr = head;
    if(curr != nullptr)
    {
        while(curr->GetNext() != nullptr)
        {
            curr = curr->GetNext();
        }
    }
    if(curr == nullptr)
    {
        AddBeginning(newnode);
    }
    else
    {
        curr->SetNext(newnode);
    }
}

SLL_Node* SLL_ADT::DeleteBeginning()
{
    SLL_Node* ans = nullptr;
    if(!IsEmpty())
    {
        ans = head;
        head = head->GetNext();
        ans->SetNext(nullptr);
    }
    return ans;
}

SLL_Node* SLL_ADT::DeleteEnd()
{
    SLL_Node* ans = nullptr;
    if(IsEmpty() || (head->GetNext() == nullptr)) ans = DeleteBeginning();
    else
    {
        SLL_Node* curr = head;
        while(((curr->GetNext())->GetNext()) != nullptr)
        {
            curr = curr->GetNext();
        }
        ans = curr->GetNext();
        curr->SetNext(nullptr);
    }
    return ans;
}

void SLL_ADT::print_list()
{
    SLL_Node* curr = head;
    cout<<"The List is:";
    while(curr != nullptr)
    {
        cout<<" "<<curr->GetData();
        curr = curr->GetNext();
    }
    cout<<endl;
}

SLL_ADT::~SLL_ADT()
{
    SLL_Node* n;
    while(!IsEmpty())
    {
        n = DeleteBeginning();
        delete n;
    }
    return;
}
