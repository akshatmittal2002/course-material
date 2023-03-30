#ifndef ARRAY_ADT_H
#define ARRAY_ADT_H


class Array_ADT
{
/// Function with same name as that of class is called a constructor and it is called automatically as soon as an object of that class is created.

/// Function with same name as that of class with a "tilde" sign (~) at beginning is called a destructor and
/// it is called automatically as soon as we end our main function.

    public:
        Array_ADT();
        Array_ADT(int);
        void SetElement(int,int);
        int GetElement(int);
        int GetCapacity();
        virtual ~Array_ADT();

    protected:

    private:
        int capacity;
        int* elements;
};

#endif // ARRAY_ADT_H
