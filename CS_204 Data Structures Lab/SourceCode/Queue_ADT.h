#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H
#include "..\SourceCode\Array_ADT.h"

class Queue_ADT
{
    public:
        Queue_ADT() = delete;
        Queue_ADT(int);
        bool IsEmpty();
        bool IsFull();
        bool Add(int);
        int Delete();
        virtual ~Queue_ADT();

        void print_queue();

    protected:

    private:
        Array_ADT members;
        int counter;
};

#endif // QUEUE_ADT_H
