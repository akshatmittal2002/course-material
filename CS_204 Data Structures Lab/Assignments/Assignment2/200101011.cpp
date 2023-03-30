#include <iostream>

using namespace std;
///=======================================================================
class circular_dll_node
{
    //Declaration of a node of our list.
    public:
        circular_dll_node(int);
        virtual ~circular_dll_node();
        int get_value();
        void set_next(circular_dll_node*);
        void set_prev(circular_dll_node*);
        void set_index(int);
        circular_dll_node* get_next();
        circular_dll_node* get_prev();
        int get_index();

    private:
        int value; //Store value of node.
        int index; //Store index of node.
        circular_dll_node* next; //Store the next pointer.
        circular_dll_node* prev; //Store the previous pointer.
};
///=======================================================================
class circular_dll
{
    //Declaration of our list.
    public:
        circular_dll();
        virtual ~circular_dll();
        void AddBeg(circular_dll_node*);
        void AddEnd(circular_dll_node*);
        void print_mirror_points();

    private:
        circular_dll_node* head; //Points to head of list.
        circular_dll_node* tail; //Points to tail of list.
        bool isempty(); //Checks if list is empty.
        void update_index(); //Update the indices of all nodes in the list.
        int get_length(); //Returns total nodes in list.
};
///=======================================================================
int main()
{
    int code = 0;
    int value = 0;
    //creates a new pointer that can point to a node of our list.
    circular_dll_node* n = nullptr;
    //This code will be 1, i.e., to create a new list.
    cin>>code;
    // Create a new list.
    circular_dll circularlist;
    //Take input till end of input file.
    while(cin>>code)
    {
        //If code is 2 or 3 create a new node with given value.
        if(code==2 || code==3)
        {
            cin>>value;
            n = new circular_dll_node(value);
            if(code==2) circularlist.AddBeg(n); //If code is 2, add node to beginning of list.
            else circularlist.AddEnd(n); //If code is 3, add node to end of list.
            n = nullptr;
        }
        else if(code==4)
        {
            circularlist.print_mirror_points(); //If code is 4, print all mirror points.
        }
        else continue;
    }
    return 0;
}
///=======================================================================
circular_dll_node::circular_dll_node(int data)
{
    //Constructor creates a new node with index 0 and data as value.
    value = data;
    next = nullptr;
    prev = nullptr;
    index = 0;
}
void circular_dll_node::set_index(int data)
{
    //Set the index to given value.
    index = data;
}
int circular_dll_node::get_index()
{
    return index;
}
int circular_dll_node::get_value()
{
    //return the value stored in node.
    return value;
}
void circular_dll_node::set_next(circular_dll_node* ptr)
{
    //Set the next pointer of node to given pointer.
    next = ptr;
}
void circular_dll_node::set_prev(circular_dll_node* ptr)
{
    //Set the previous pointer of node to given pointer.
    prev = ptr;
}
circular_dll_node* circular_dll_node::get_next()
{
    //Return the next pointer.
    return next;
}
circular_dll_node* circular_dll_node::get_prev()
{
    //Return the previous pointer.
    return prev;
}
circular_dll_node::~circular_dll_node()
{
    //Destructor.
    return;
}
///=======================================================================
circular_dll::circular_dll()
{
    //Constructor of out list set head and tail pointer to NULL.
    head = nullptr;
    tail = nullptr;
}
bool circular_dll::isempty()
{
    //Checks if list is empty or not.
    if(head==nullptr && tail==nullptr) return true;
    else return false;
}
void circular_dll::AddBeg(circular_dll_node* node)
{
    //Add a node at beginning of list.
    if(isempty())
    {
        head = node;
        tail = node;
        node->set_next(tail);
        node->set_prev(head);
    }
    else
    {
        node->set_next(head);
        head->set_prev(node);
        tail->set_next(node);
        node->set_prev(tail);
        head = node;
    }
}
void circular_dll::AddEnd(circular_dll_node* node)
{
    //Add a node at end of list.
    if(isempty())
    {
        head = node;
        tail = node;
        node->set_next(tail);
        node->set_prev(head);
    }
    else
    {
        node->set_prev(tail);
        tail->set_next(node);
        head->set_prev(node);
        node->set_next(head);
        tail = node;
    }
}
void circular_dll::update_index()
{
    //Update the indices of nodes of list.
    //I used it only before printing since in other places we do not require these indices.
    //The first node will be index 0.
    circular_dll_node* curr = head;
    if(curr == nullptr) return;
    int i=0;
    do
    {
        curr->set_index(i);
        i++;
        curr = curr->get_next();
    }while(curr != head);
    return;
}
int circular_dll::get_length()
{
    //Returns length of list, i.e., total nodes in lists.
    int ans = 0;
    circular_dll_node* curr = head;
    if(curr == nullptr);
    else
    {
        do
        {
            ans++;
            curr = curr->get_next();
        }while(curr != head);
    }
    return ans;
}
void circular_dll::print_mirror_points()
{
    //Prints the mirror indices.
    //First update the indices of all nodes in list.
    update_index();
    //Set a variable to keep track of total mirror indices.
    int total = 0;
    //An array just to store the indices which turned out to be mirror points.
    int* a = new int[get_length()];
    //If list is not empty then traverse list to find mirror points.
    if(!isempty())
    {
        //Pointer CW (clockwise) to traverse the list in clockwise direction.
        circular_dll_node* cw = nullptr;
        //Pointer CCW (counter-clockwise) to traverse the list in counter-clockwise direction.
        circular_dll_node* ccw = nullptr;
        //Pointer current to point on current element being checked.
        circular_dll_node* curr = head;
        do
        {
            //Set CW to next element of current and CCW to previous element of current.
            cw = curr->get_next();
            ccw = curr->get_prev();
            //Checks all the elements until CW and CCW points to same element.
            while(cw != ccw)
            {
                //If the elements are same then move to next step else break the loop.
                if(cw->get_value() == ccw->get_value())
                {
                    cw = cw->get_next();
                    ccw = ccw ->get_prev();
                }
                else break;
            }
            //Now if all elements of the above loop are same CW becomes equal to CCW and hence the current is a mirror index.
            if(cw == ccw)
            {
                a[total] = curr->get_index();
                total++;
            }
            //Then check next element.
            curr = curr->get_next();
        }while(curr != head);//if current becomes head again, we are done!
    }
    cout<<"Total mirror points: "<<total<<" Indices:";
    for(int i=0; i<total; i++)
    {
        cout<<" "<<a[i];
    }
    cout<<endl;
    delete[] a;
}
circular_dll::~circular_dll()
{
    //Destructor will delete all nodes of our lists and free the memory.
    circular_dll_node* ans = nullptr;
    while(1)
    {
        if(isempty());
        else if(head == tail)
        {
            tail = nullptr;
            ans = head;
            head = nullptr;
            ans->set_next(nullptr);
            ans->set_prev(nullptr);
        }
        else
        {
            ans = head;
            head = head->get_next();
            head->set_prev(tail);
            ans->set_next(nullptr);
            ans->set_prev(nullptr);
            tail->set_next(head);
        }
        if(ans==nullptr) break;
        delete ans;
    }
    return;
}
