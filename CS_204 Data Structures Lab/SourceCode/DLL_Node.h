#ifndef DLL_NODE_H
#define DLL_NODE_H

class DLL_Node
{
    public:
        DLL_Node(int);
        int GetData();
        DLL_Node* GetNext();
        DLL_Node* GetPrev();
        void SetNext(DLL_Node*);
        void SetPrev(DLL_Node*);
        virtual ~DLL_Node();

    protected:

    private:
        int data;
        DLL_Node* prev;
        DLL_Node* next;
};

#endif // DLL_NODE_H
