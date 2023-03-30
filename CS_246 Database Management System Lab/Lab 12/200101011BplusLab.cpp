#include <bits/stdc++.h>
using namespace std;

class Bplus_node;
class node{
    public:
        int data;
        Bplus_node *left;
        node(){
            left = nullptr;
        }
};

class Bplus_node{
    public:
        vector<node *> content;
        bool isDataNode;
        Bplus_node *right;
        Bplus_node *parent;
        Bplus_node(){
            right = nullptr;
            parent = nullptr;
            isDataNode = false;
        }
};

class Bplus_tree{
    public:
        Bplus_node *root;
        int d, t;
        Bplus_tree(int d, int t){
            root = nullptr;
            this->d = d;
            this->t = t;
        }
        void insert(int data);
        int CountIndex(Bplus_node *node);
        int CountData(Bplus_node *node);
        void display();
};

bool cmp(node* &a, node* &b){
    return (a->data) < (b->data);
}

int main(){
    int d, t;
    cin>>d>>t;
    Bplus_tree tree(d, t);
    int x,value;
    cin>>x;
    while (x != 3){
        if (x == 1){
            cin>>value;
            // cout<<"Inserting "<<value<<"\n";
            tree.insert(value);
        }
        else if (x == 2){
            tree.display();
        }
        cin>>x;
    }
    return 0;
}

void Bplus_tree::display(){
    if (root == nullptr){
        cout<<"0 0\n";
        return;
    };
    cout<<CountIndex(root)<<" "<<CountData(root);
    for (int i = 0; i < root->content.size(); i++){
        cout<<" "<<(root->content[i])->data;
    }
    cout<<"\n";
}

int Bplus_tree::CountData(Bplus_node *node){
    if (node == nullptr) return 0;
    if (node->isDataNode == true) return 1;
    int k = 0;
    for (int i = 0; i < node->content.size(); i++){
        k += CountData((node->content[i])->left);
    }
    k += CountData(node->right);
    return k;
}

int Bplus_tree::CountIndex(Bplus_node *node){
    if (node == nullptr) return 0;
    if (node->isDataNode == true) return 0;
    int k = 1;
    for (int i = 0; i < node->content.size(); i++){
        k += CountIndex((node->content[i])->left);
    }
    k += CountIndex(node->right);
    return k;
}

void Bplus_tree::insert(int data){
    node* n;
    // First Insertion, i.e., root is null
    if (root == nullptr){
        Bplus_node *x = new Bplus_node(); // Create a new data node
        x->isDataNode = true;
        // cout<<"Data Node ++\n";
        n = new node(); // Create a new entry in this data node
        n->data = data;
        x->content.push_back(n);
        root = x; //Set root of B Plus tree to this new data node
        return;
    }
    // Root is a Data Node
    if (root->isDataNode == true){
        // Root is not full
        if (root->content.size() < 2*d){
            n = new node(); // Create a new entry in the root
            n->data = data;
            n->left = nullptr;
            root->content.push_back(n);
            sort(root->content.begin(), root->content.end(), cmp); // Sort the elements in data node
        }
        // Root is full
        else{
            n = new node(); // Create a new entry in current root
            n->data = data;
            n->left = nullptr;
            root->content.push_back(n);
            sort(root->content.begin(), root->content.end(), cmp); // Sort the contents
            Bplus_node *right_node = new Bplus_node(); // Create a new data node
            right_node->isDataNode = true;
            // cout<<"Data Node ++\n";
            //Split the current data node in two parts: d and d+1
            for (int i = d; i < root->content.size(); i++){
                n = new node();
                n->data = (root->content[i])->data;
                n->left = nullptr;
                right_node->content.push_back(n);
            }
            for (int i = 0; i <= d; i++){
                n = root->content.back();
                root->content.pop_back();
                delete(n);
            }
            // Now create new index node and insert the smallest entry of right data node in this.
            Bplus_node *new_root = new Bplus_node();
            // cout<<"Index Node ++\n";
            n = new node();
            n->data = (right_node->content[0])->data;
            n->left = root;
            new_root->content.push_back(n);
            new_root->right = right_node;
            root->parent = new_root;
            right_node->parent = new_root;
            root = new_root; // Set root to new index node and also set parent pointers.
        }
        return;
    }
    // Root is index node
    // Find the data node in which new value is to be inserted
    Bplus_node* curr = nullptr;
    Bplus_node* next = root;
    int k;
    while (next->isDataNode == false){
        if(next->content.size() == (2*t+1)){
            // cout<<"Split Node\n";
            Bplus_node* right_node = new Bplus_node();
            // cout<<"Index Node ++\n";
            int value_up = (next->content[t])->data;
            right_node->right = next->right;
            next->right = (next->content[t])->left;
            (next->content[t])->left = nullptr;
            for (int i = t+1; i <= 2*t; i++){
                n = new node();
                n->data = (next->content[i])->data;
                n->left = (next->content[i])->left;
                right_node->content.push_back(n);
            }
            for(int i=0; i<right_node->content.size(); i++){
                ((right_node->content[i])->left)->parent = right_node;
            }
            (right_node->right)->parent = right_node;
            // cout<<"DONE 1\n";
            for (int i = t; i<=2*t; i++){
                n = next->content.back();
                next->content.pop_back();
                delete(n);
            }
            // cout<<"DONE 2\n";
            n = new node();
            n->data = value_up;
            n->left = next;
            // cout<<"DONE 3\n";
            if(curr != nullptr){
                // cout<<"Split Non Root Node\n";
                right_node->parent = curr;
                if (n->data > (curr->content.back())->data){
                    curr->content.push_back(n);
                    curr->right = right_node;
                }
                else{
                    curr->content.push_back(n);
                    sort(curr->content.begin(), curr->content.end(), cmp);
                    int j = 0;
                    for (j = 0; j < curr->content.size(); j++){
                        if (curr->content[j]->data == n->data){
                            break;
                        }
                    }
                    curr->content[j+1]->left = right_node;
                }
                next = curr;
            }
            else{
                // cout<<"Split Root Node\n";
                Bplus_node* new_root = new Bplus_node();
                // cout<<"Index Node ++\n";
                new_root->content.push_back(n);
                new_root->right = right_node;
                next->parent = new_root;
                right_node->parent = new_root;
                root = new_root;
                next = root;
            }
        }
        k = 0;
        curr = next;
        for (int i = 0; i < curr->content.size(); i++){
            if ((curr->content[i])->data > data){
                k = 1;
                next = (curr->content[i])->left;
                // cout<<"Descend to "<<i<<" child\n";
                break;
            }
        }
        if (k == 0){
            next = curr->right;
            // cout<<"Descend to right child\n";
        }
    }
    curr = next;
    // Once the correct Data node (curr) is found, check if it is full or not
    // If not full
    if (curr->content.size() < 2*d){
        n = new node(); // Just create a new entry in the data node
        n->data = data;
        n->left = nullptr;
        curr->content.push_back(n);
        sort(curr->content.begin(), curr->content.end(), cmp); // Sort the elements
        // cout<<"Inserted In Non Full Data Node "<<curr->content[0]->data<<"\n";
    }
    // Else if full
    else{
        n = new node(); // Create a new entry in this data node
        n->data = data;
        n->left = nullptr;
        curr->content.push_back(n);
        sort(curr->content.begin(), curr->content.end(), cmp); // Sort the values
        Bplus_node *right_node = new Bplus_node(); // Create a new data node
        right_node->isDataNode = true;
        // cout<<"Data Node ++\n";
        //Split the current data node in two parts: d and d+1
        for (int i = d; i < curr->content.size(); i++){
            n = new node();
            n->data = curr->content[i]->data;
            n->left = nullptr;
            right_node->content.push_back(n);
        }
        for (int i = 0; i<d+1; i++){
            n = curr->content.back();
            curr->content.pop_back();
            delete(n);
        }
        right_node->parent = curr->parent; // Set parent pointer
        // cout<<"Inserted In Full Data Node "<<right_node->content[0]->data<<"\n";
        // Send index value to the parent
        n = new node(); // New Entry in Parent
        n->data = (right_node->content[0])->data; // It's value is smallest value in right child
        n->left = curr; // Set left child
        // If new entry is largest entry of index node, just insert it and update the right child pointer
        if (n->data > ((curr->parent)->content.back())->data){
            (curr->parent)->content.push_back(n);
            (curr->parent)->right = right_node;
        }
        // Else we have to update some other pointer
        else{
            (curr->parent)->content.push_back(n); // Insert into index node
            Bplus_node *curr_parent = curr->parent;
            sort(curr_parent->content.begin(), curr_parent->content.end(), cmp); // Sort the index node
            int j = 0; // Find the location where pointers need to be updated and update it.
            for (j = 0; j < curr_parent->content.size(); j++){
                if (curr_parent->content[j]->data == n->data){
                    break;
                }
            }
            curr_parent->content[j+1]->left = right_node;
        }
        // cout<<"Added Middle To Index\n";
    }
}