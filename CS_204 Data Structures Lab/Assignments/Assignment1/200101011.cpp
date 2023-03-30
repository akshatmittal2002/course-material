#include <iostream>

using namespace std;
///========================================================
///Declaration of our STACK class.
class Stack_ADT
{
    public:
        Stack_ADT(int); //Constructor will create a new stack with given size.
        void push(int); //Reverse the stack and then push elements to stack.
        void pop(); //Pop element from stack and then reverse the satck.
        void print_stack(); //Print the current stack.
        virtual ~Stack_ADT(); //Destructor.

    private:

        int counter; //Variable to keep track of current number of elements in stack.
        int capacity; //Variable to store the size of our stack.
        int* a; //Pointer to create an array to build our stack.

        bool IsEmpty(); //Checks if our stack is empty.
        bool IsFull(); //Checks if our stack is full.
        void reverse_stack(); //Reverse our stack.
};
///========================================================
///Start of our main function
int main()
{
    //Declaring required variables.
    int inputcode=0;
    int value=0;

    //Take in the first input code that will be '1' to create a new stack.
    cin>>inputcode;
    //Take in the size of stack to be created.
    cin>>value;

    //Create an object of Stack_ADT class, i.e., a new stack with required size.
    Stack_ADT s(value);

    //Now take input till end.
    while(cin>>inputcode)
    {
        //If code is '2'; take in the value and insert it in our stack.
        if(inputcode==2)
        {
            cin>>value;
            s.push(value);
        }
        //If code is '3'; delete from our stack.
        else if(inputcode==3)
        {
            s.pop();
        }
        //If code is '7'; print the stack.
        else if(inputcode==7)
        {
            s.print_stack();
        }
        //Else the input is invalid, discard it and take next input.
        else
        {
            continue;
        }
    }
    ///MY CODE WILL CREATE ONLY SINGLE STACK, i.e., IT WILL TAKE '1' AS INPUT ONLY SINGLE TIME.
    ///ALSO, IF THERE IS ANY INVALID INPUT; MY CODE WILL TAKE IT AND JUST DISCARD IT.
    ///ALSO, IF AN ELEMENT IS TRIED TO BE PUSHED INTO FULL STACK OR POPPED FROM AN EMPTY STACK; MY CODE TAKE THE CORRESPONDING INPUT AND DISCARD IT.
    return 0;
}
///========================================================
///Function Definition of various functions in our stack class.
Stack_ADT::Stack_ADT(int x)
{
    //Creates a stack of particular capacity.
    counter = 0; //Since no elements; counter = 0.
    capacity = x; //Assign capacity the value x.
    a = new int[x]; //New Array of size "capacity".
}

bool Stack_ADT::IsEmpty()
{
    //Our Stack is empty iff counter=0.
    if(counter==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Stack_ADT::IsFull()
{
    //Our Stack is empty iff counter=capacity.
    if(counter==capacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Stack_ADT::push(int val)
{
   //We will insert iff stack is not full.
   if(!IsFull())
   {
       //First reverse the stack.
       reverse_stack();
       //Then add the element.
       a[counter] = val;
       //Since an element is added; counter needs to be increased by 1.
       counter++;
       return;
   }
   return;
}

void Stack_ADT::pop()
{
    //We will delete iff stack is not empty.
    if(!IsEmpty())
    {
        //We only delete element from stack but it will still remain in memory.
        //Since an element is deleted; counter needs to be decreased by 1.
        counter--;
        //Then reverse the stack.
        reverse_stack();
        return;
    }
    return;
}

void Stack_ADT::print_stack()
{
    //First print number of elements.
    cout<<counter<<" elements:";
    //Then print stack's elements one by one.
    for(int i=0; i<counter; i++)
    {
        cout<<" "<<a[i];
    }
    //Print a new line at end.
    cout<<endl;
    return;
}

void Stack_ADT::reverse_stack()
{
    //A variable to store an element temporary.
    int temp = 0;
    //Traverse till middle of stack.
    for(int i=0; i<(counter/2); i++)
    {
        //Swap i(th) element from starting with i(th) element from end in order the reverse whole stack.
        temp = a[i];
        a[i] = a[counter-i-1];
        a[counter-i-1] = temp;
    }
    return;
}

Stack_ADT::~Stack_ADT()
{
    //Free up the allocated memory inside destructor.
    delete[] a;
}
///========================================================
