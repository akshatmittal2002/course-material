#ifndef CIRCULAR_QUEUE_ADT_H
#define CIRCULAR_QUEUE_ADT_H
#include "..\SourceCode\Array_ADT.h"

class Circular_Queue_ADT
{
    public:
        Circular_Queue_ADT() = delete;
        Circular_Queue_ADT(int);
        bool IsFull();
        bool IsEmpty();
        bool Add(int);
        int Delete();
        virtual ~Circular_Queue_ADT();

        void print_circular_queue();

    protected:

    private:
        int head;
        int tail;
        Array_ADT members;
        int successor(int);///As we don't require this function to be available for use outside our class.
};

#endif // CIRCULAR_QUEUE_ADT_H
