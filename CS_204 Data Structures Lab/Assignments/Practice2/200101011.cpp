#include <iostream>
using namespace std;
///======================================================
class BST_node
{
    public:
        BST_node(int);
        virtual ~BST_node();
        int getdata();
        void setleft(BST_node*);
        void setright(BST_node*);
        BST_node* getleft();
        BST_node* getright();

    private:
        int data;
        BST_node* left;
        BST_node* right;
};
///======================================================
class BST
{
    public:
        BST();
        virtual ~BST();
        void addnode(BST_node*);
        void print_inorder();
        BST_node* searchtree(int);
        BST_node* minimum();
        BST_node* maximum();
        BST_node* find_succ(int);
        BST_node* find_pred(int);

    private:
        BST_node* root;
        void inorder(BST_node*);
        BST_node* searchinside(int,BST_node*);
        BST_node* minimuminside(BST_node*);
        BST_node* maximuminside(BST_node*);
};
///======================================================
int main()
{
    BST tree;
    BST_node* n;
    int code,value;
    cout<<"Type 1 to add a node in tree.\n";
    cout<<"Type 2 to search a value in tree.\n";
    cout<<"Type 3 to get minimum value in tree.\n";
    cout<<"Type 4 to get maximum value in tree.\n";
    cout<<"Type 5 to get successor of an element in tree.\n";
    cout<<"Type 6 to get predecessor of an element in tree.\n";
    cout<<"Type 7 to print the tree in in-order.\n";
    cout<<"Type 8 to quit.\n";
    while(1){
        cout<<"\nENTER CODE: ";
        cin>>code;
        if(code==1){
            cout<<"ENTER VALUE: ";
            cin>>value;
            n = new BST_node(value);
            tree.addnode(n);
        }
        else if(code==2){
            cout<<"ENTER VALUE: ";
            cin>>value;
            if(tree.searchtree(value)) cout<<"YES\n";
            else cout<<"NO\n";
        }
        else if(code==3) cout<<"MINIMUM: "<<tree.minimum()->getdata()<<endl;
        else if(code==4) cout<<"MAXIMUM: "<<tree.maximum()->getdata()<<endl;
        else if(code==5 || code==6){
            cout<<"ENTER VALUE: ";
            cin>>value;
            if(code==5){
                BST_node* ans = tree.find_succ(value);
                if(ans==nullptr) cout<<tree.maximum()->getdata()<<" is the largest element in tree.\nCould not find successor of "<<value<<endl;
                else cout<<"Successor of "<<value<<" in tree: "<<ans->getdata()<<endl;
            }
            else{
                BST_node* ans = tree.find_pred(value);
                if(ans==nullptr) cout<<tree.minimum()->getdata()<<" is the smallest element in tree.\nCould not find predecessor of "<<value<<endl;
                else cout<<"Predecessor of "<<value<<" in tree: "<<ans->getdata()<<endl;
            }
        }
        else if(code==7){
            cout<<"TREE DATA: ";
            tree.print_inorder();
        }
        else if(code==8) break;
        else cout<<"INVALID CODE\n";
    }
    return 0;
}
///======================================================
BST_node::BST_node(int value){
    data = value;
    left = nullptr;
    right = nullptr;
}
int BST_node::getdata(){
    return data;
}
void BST_node::setleft(BST_node* node){
    left = node;
}
void BST_node::setright(BST_node* node){
    right = node;
}
BST_node* BST_node::getleft(){
    return left;
}
BST_node* BST_node::getright(){
    return right;
}
BST_node::~BST_node(){
}
///======================================================
BST::BST(){
    root = nullptr;
}
void BST::addnode(BST_node* newnode){
    if(root==nullptr){
        root = newnode;
        return;
    }
    BST_node* curr = root;
    while(1){
        if(newnode->getdata() <= curr->getdata()){
            if(curr->getleft()==nullptr){
                curr->setleft(newnode);
                return;
            }
            else curr = curr->getleft();
        }
        else{
            if(curr->getright()==nullptr){
                curr->setright(newnode);
                return;
            }
            else curr = curr->getright();
        }
    }
}
BST_node* BST::searchinside(int value,BST_node* node){
    if(node==nullptr) return nullptr;
    if(value==node->getdata()) return node;
    if(value<node->getdata()) return searchinside(value,node->getleft());
    else return searchinside(value,node->getright());
}
BST_node* BST::searchtree(int value){
    return searchinside(value,root);
}
void BST::inorder(BST_node* node){
    if(node==nullptr) return;
    inorder(node->getleft());
    cout<<node->getdata()<<" ";
    inorder(node->getright());
}
void BST::print_inorder(){
    inorder(root);
    cout<<endl;
}
BST_node* BST::minimum(){
    return minimuminside(root);
}
BST_node* BST::maximum(){
    return maximuminside(root);
}
BST_node* BST::minimuminside(BST_node* node){
    BST_node* curr = node;
    while(curr->getleft()) curr = curr->getleft();
    return curr;
}
BST_node* BST::maximuminside(BST_node* node){
    BST_node* curr = node;
    while(curr->getright()) curr = curr->getright();
    return curr;
}
BST_node* BST::find_succ(int value){
    if(root==nullptr) return nullptr;
    BST_node* curr = root;
    BST_node* ans = nullptr;
    while(curr){
        if(curr->getdata() == value){
            if(curr->getright()) ans = minimuminside(curr->getright());
            break;
        }
        else if(curr->getdata() > value){
            ans = curr;
            curr = curr->getleft();
        }
        else curr = curr->getright();
    }
    return ans;
}
BST_node* BST::find_pred(int value){
    if(root==nullptr) return nullptr;
    BST_node* curr = root;
    BST_node* ans = nullptr;
    while(curr){
        if(curr->getdata() == value){
            if(curr->getleft()) ans = maximuminside(curr->getleft());
            break;
        }
        else if(curr->getdata() > value) curr = curr->getleft();
        else{
            ans = curr;
            curr = curr->getright();
        }
    }
    return ans;
}
BST::~BST(){
}
