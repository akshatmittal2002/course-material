#ifndef DLL_ADT_H
#define DLL_ADT_H
#include "..\SourceCode\DLL_Node.h"

class DLL_ADT
{
    public:
        DLL_ADT();
        void AddBeginning(DLL_Node*);
        void AddEnd(DLL_Node*);
        void print_list();
        DLL_Node* DeleteBeginning();
        DLL_Node* DeleteEnd();
        virtual ~DLL_ADT();

    protected:

    private:
        DLL_Node* head;
        DLL_Node* tail;
        bool IsEmpty();
};

#endif // DLL_ADT_H
