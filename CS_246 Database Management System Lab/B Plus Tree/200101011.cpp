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
    node *n;
    // First Insertion, i.e., root is null
    if (root == nullptr){
        Bplus_node *x = new Bplus_node(); // Create a new data node
        x->isDataNode = true;
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
            root->content.push_back(n);
            sort(root->content.begin(), root->content.end(), cmp); // Sort the elements in data node
        }
        // Root is full
        else{
            n = new node(); // Create a new entry in current root
            n->data = data;
            root->content.push_back(n);
            sort(root->content.begin(), root->content.end(), cmp); // Sort the contents

            Bplus_node *right_node = new Bplus_node(); // Create a new data node
            right_node->isDataNode = true;
            //Split the current data node in two parts: d and d+1
            for (int i = d; i < root->content.size(); i++){
                n = new node();
                n->data = (root->content[i])->data;
                right_node->content.push_back(n);
            }
            for (int i = 0; i <= d; i++){
                n = root->content.back();
                root->content.pop_back();
                delete(n);
            }
            // Now create new index node and insert the smallest entry of right data node in this.
            Bplus_node *new_root = new Bplus_node();
            n = new node();
            n->data = (right_node->content[0])->data;
            n->left = root;
            new_root->content.push_back(n);
            new_root->right = right_node;
            root = new_root; // Set root to new index node and also set parent pointers.
            ((root->content[0])->left)->parent = root;
            (root->right)->parent = root;
        }
        return;
    }
    // Root is index node
    // Find the data node in which new value is to be inserted
    Bplus_node *curr = root;
    int k;
    while (curr->isDataNode == false){
        k = 0;
        for (int i = 0; i < curr->content.size(); i++){
            if (curr->content[i]->data > data){
                k = 1;
                curr = (curr->content[i])->left;
                break;
            }
        }
        if (k == 0){
            curr = curr->right;
        }
    }
    // Once the correct Data node is found, check if it is full or not
    // If not full
    if (curr->content.size() < 2 * d){
        n = new node(); // Just create a new entry in the data node
        n->data = data;
        curr->content.push_back(n);
        sort(curr->content.begin(), curr->content.end(), cmp); // Sort the elements
        return;
    }
    // Else if full
    n = new node(); // Create a new entry in this data node
    n->data = data;
    curr->content.push_back(n);
    sort(curr->content.begin(), curr->content.end(), cmp); // Sort the values
    Bplus_node *right_node = new Bplus_node(); // Create a new data node
    right_node->isDataNode = true;
    //Split the current data node in two parts: d and d+1
    for (int i = d; i < curr->content.size(); i++){
        n = new node();
        n->data = curr->content[i]->data;
        right_node->content.push_back(n);
    }
    for (int i = 0; i < d + 1; i++){
        n = curr->content.back();
        curr->content.pop_back();
        delete(n);
    }
    right_node->parent = curr->parent; // Set parent pointer

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
        curr_parent->content[j + 1]->left = right_node;
    }
    curr = curr->parent;
    if (curr == nullptr){
        return;
    }
    // If index node exeecds maximum capacity
    while (curr->content.size() > (2*t+1)){
        // Special root case, to be handled after this loop
        if (curr == root || curr == nullptr){
            break;
        }
        // Split the current index node
        Bplus_node *right_node = new Bplus_node(); // Create a new index node
        int value_up = curr->content[t]->data; // The value to be sent to parent after splitting
        // Split into t,1,t+1; 1->up to parent
        for (int i = t + 1; i < curr->content.size(); i++){
            n = new node();
            n->data = curr->content[i]->data;
            n->left = curr->content[i]->left;
            right_node->content.push_back(n);
        }
        // Update all pointers
        right_node->parent = curr->parent;
        right_node->right = curr->right;
        curr->right = curr->content[t]->left; // Left child of the value to be sent to parent
        // Delete the nodes transfered to new node and parent
        for (int i = 0; i < t + 2; i++){
            n = curr->content.back();
            curr->content.pop_back();
            delete(n);
        }
        // Update parent pointer of children of splitted index node
        for (int i = 0; i < right_node->content.size(); i++){
            ((right_node->content[i])->left)->parent = right_node;
        }
        (right_node->right)->parent = right_node;

        // Insert the middle value into parent node.
        n = new node();
        n->data = value_up;
        n->left = curr;
        // If new entry is largest entry of index node, just insert it and update the right child pointer
        if (n->data > ((curr->parent)->content.back())->data){
            (curr->parent)->content.push_back(n);
            (curr->parent)->right = right_node;
        }
        // Else we have to update some other pointer
        else{
            (curr->parent)->content.push_back(n); // Insert into parent node
            Bplus_node *curr_parent = curr->parent;
            sort(curr_parent->content.begin(), curr_parent->content.end(), cmp); // Sort the parent node
            int j = 0; // Find the location where pointers need to be updated and update it.
            for (j = 0; j < curr_parent->content.size(); j++){
                if (curr_parent->content[j]->data == n->data){
                    break;
                }
            }
            curr_parent->content[j + 1]->left = right_node;
        }
        curr = curr->parent;
    }
    // Now after exiting the loop, current pointer will be pointing to root
    // If it exeeds the max capacity, split the root.
    if (curr == root && curr->content.size() > (2*t+1)){
        // Create a new index node
        Bplus_node *right_node = new Bplus_node();
        int value_up = curr->content[t]->data; // Middle value to be sent to new root.
        // Split into t,1,t+1; 1->up to parent
        for (int i = t+1; i < root->content.size(); i++){
            n = new node();
            n->data = root->content[i]->data;
            n->left = root->content[i]->left;
            right_node->content.push_back(n);
        }
        // Update pointers
        right_node->right = curr->right;
        curr->right = (curr->content[t])->left; // Left child of the value to be sent to parent
        // Delete the nodes transfered to new node and parent
        for (int i = 0; i < t + 2; i++){
            n = root->content.back();
            root->content.pop_back();
            delete(n);
        }
        // Update parent pointer of children of splitted index node
        for (int i = 0; i < right_node->content.size(); i++){
            right_node->content[i]->left->parent = right_node;
        }
        right_node->right->parent = right_node;
        // Create a new root
        Bplus_node *new_root = new Bplus_node();
        // Insert the value into root
        n = new node();
        n->data = value_up;
        n->left = root;
        new_root->content.push_back(n);
        new_root->right = right_node;
        // Update new root
        root = new_root;
        ((root->content[0])->left)->parent = root;
        (root->right)->parent = root;
    }
}