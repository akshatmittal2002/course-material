#ifndef SLL_NODE_H
#define SLL_NODE_H

class SLL_Node
{
    public:
        SLL_Node(int);
        int GetData();
        SLL_Node* GetNext();
        void SetNext(SLL_Node*);
        virtual ~SLL_Node();

    protected:

    private:
        int data;
        SLL_Node* next;
};

#endif // SLL_NODE_H
