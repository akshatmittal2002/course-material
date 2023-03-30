#ifndef SLL_ADT_H
#define SLL_ADT_H
#include "..\SourceCode\SLL_Node.h"

class SLL_ADT
{
    public:
        SLL_ADT();
        void AddBeginning(SLL_Node*);
        void AddEnd(SLL_Node*);
        void print_list();
        SLL_Node* DeleteBeginning();
        SLL_Node* DeleteEnd();
        virtual ~SLL_ADT();

    protected:

    private:
        SLL_Node* head;
        bool IsEmpty();
};

#endif // SLL_ADT_H
