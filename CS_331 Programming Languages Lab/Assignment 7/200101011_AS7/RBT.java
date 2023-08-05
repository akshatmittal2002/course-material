import java.util.*;
import java.io.*;

public class RBT{
    // Class for a node in the Red Black Tree
    public class Node{
        public int key; // Key of the node
        public Node left; // Left child of the node
        public Node right; // Right child of the node
        public Node parent; // Parent of the node
        public char color; // Color of the node (r for red, b for black)
        // Constructor for the node
        Node(int key){
            this.key = key;
            this.left = null;
            this.right = null;
            this.parent = null;
            this.color = 'r'; // Initially node is red
        }
    }
    
    public Node root; // Root of the Red Black Tree
    public Node nil; // Sentinel node
    
    // Constructor for the Red Black Tree
    RBT(){
        this.nil = new Node(-1);
        this.nil.color = 'b'; // Sentinel node is black
        this.root = this.nil;
    }
    
    // Function to search for a key in the Red Black Tree
    public Node Search(int key){
        // Start searching from the root
        Node curr = this.root;
        while(curr != this.nil){
            // If key is found, return node
            if(key == curr.key) break;
            // Else if key is less than node's key, search in left subtree
            else if(key < curr.key) curr = curr.left;
            // Else if key is greater than node's key, search in right subtree
            else curr = curr.right;
        }
        return curr;
    }
    
    // Function to perform left rotation about a node
    private void LeftRotate(Node x){
        Node par = x.parent; // Parent of x
        Node alpha = x.right; // Right child of x
        Node beta = alpha.left; // Left child of alpha (right child of x)
        // Perform rotation
        alpha.left = x;
        x.parent = alpha;
        x.right = beta;
        beta.parent = x;
        alpha.parent = par;
        // If x was not the root, make alpha the child of x's parent
        if(par != this.nil){
            if(par.left == x) par.left = alpha;
            else par.right = alpha;
        }
        // Else, make alpha the root
        else{
            this.root = alpha;
        }
    }
    
    // Function to perform right rotation about a node
    private void RightRotate(Node x){
        Node par = x.parent; // Parent of x
        Node alpha = x.left; // Left child of x
        Node beta = alpha.right; // Right child of alpha (left child of x)
        // Perform rotation
        alpha.right = x;
        x.parent = alpha;
        x.left = beta;
        beta.parent = x;
        alpha.parent = par;
        // If x was not the root, make alpha the child of x's parent
        if(par != this.nil){
            if(par.left == x) par.left = alpha;
            else par.right = alpha;
        }
        // Else, make alpha the root
        else{
            this.root = alpha;
        }
    }

    // Function to print the tree in inorder
    public void PrintInorder(){
        Stack<Node> stack = new Stack<Node>();
        Node curr = this.root;
        // Traverse the tree in inorder
        while(!stack.isEmpty() || curr != this.nil){
            // Push all the left children of the current node to the stack till we reach the leftmost node
            while(curr != this.nil){
                stack.push(curr);
                curr = curr.left;
            }
            // Print the leftmost node
            curr = stack.pop();
            System.out.print(curr.key + " ");
            // Move to the right child of the leftmost node
            curr = curr.right;
            // Repeat the process for the right subtree till stack is not empty
        }
        System.out.println();
    }

    // Function to insert a key in the Red Black Tree
    public boolean Insert(int key){
        // Search if the key is already present in the tree
        Node node = Search(key);
        // If key is already present, return
        if(node != this.nil){
            return false;
        }
        // Create a new node
        node = new Node(key);
        // Initialize the node
        node.parent = node.right = node.left = this.nil;
        // If tree is empty, make node the root
        if(this.root == this.nil){
            this.root = node;
            node.color = 'b'; // Root is always black
            return true;
        }
        // Else, find the correct position for the node
        Node curr = this.root;
        Node par = curr;
        while(curr != nil){
            par = curr;
            if(node.key <= curr.key) curr = curr.left;
            else curr = curr.right;
        }
        // Insert the node at the correct position
        node.parent = par;
        if(node.key <= par.key) par.left = node;
        else par.right = node;
        curr = node;

        // Fix up the tree
        // If parent is black, no need to fix up, Case 1
        while(curr.parent.color == 'r'){
            par = curr.parent;
            Node grandpar = par.parent;
            Node uncle = grandpar;
            // If parent is left child of grandparent
            if(par == grandpar.right){
                uncle = grandpar.left;
                // If uncle is red, Case 2b
                if(uncle.color == 'r'){
                    par.color = 'b';
                    grandpar.color = 'r';
                    uncle.color = 'b';
                    curr = grandpar;
                }
                // Else uncle is black, Case 2a
                else{
                    // If curr is right child of parent, Case 3
                    if(curr == par.left){
                        RightRotate(par);
                        curr = par;
                        par = curr.parent;
                    }
                    // Now apply Case 2a
                    par.color = 'b';
                    grandpar.color = 'r';
                    LeftRotate(grandpar);
                }
            }
            // else parent is right child of grandparent, similar to above with left and right interchanged
            else{
                uncle = grandpar.right;
                // If uncle is red, Case 2b
                if(uncle.color == 'r'){
                    par.color = 'b';
                    grandpar.color = 'r';
                    uncle.color = 'b';
                    curr = grandpar;
                }
                // Else uncle is black, Case 2a
                else{
                    // If curr is right child of parent, Case 3
                    if(curr==par.right){
                        LeftRotate(par);
                        curr = par;
                        par = curr.parent;
                    }
                    // Now apply Case 2a
                    par.color = 'b';
                    grandpar.color = 'r';
                    RightRotate(grandpar);
                }
            }
        }
        // Make root black in case it is red
        this.root.color = 'b';
        return true;
    }
    
    // Function to generate the graphviz code for the tree and generate the image
    public void showGraph(int num){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("graph_" + num + ".dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "digraph G {\nnode [shape=circle];\n";
        entry += "root [label=\"Root\", shape = plaintext]\n";
        // Traverse the tree in preorder and add the nodes
        Stack<Node> stack = new Stack<Node>(); // Stack to store the nodes
        Node curr = this.root; // Start from the root
        int cnt = 0; // Counter to keep track of nil nodes
        while(curr != this.nil || !stack.isEmpty()){
            // Push all the left children of the current node to the stack till we reach the leftmost node
            while(curr != this.nil){
                // Print the node
                entry += curr.key + "[color=" + (curr.color == 'r' ? "red" : "black fontcolor=white") + " style=filled fontname=bold]\n";
                // Print the edge from the parent to the node
                if(curr == this.root){
                    entry += "root -> " + this.root.key + "\n";
                }
                else{
                    entry += curr.parent.key + " -> " + curr.key + ";\n";
                }
                stack.push(curr);
                curr = curr.left;
            }
            // Print the nil nodes
            entry += "nil" + cnt + "[label=\"NIL\" shape = record color=black fontcolor=white style=filled height=0.01 width=0.01]\n";
            cnt++;
            curr = stack.pop();
            // Print the edge from the parent to the nil node
            if(curr.left == this.nil){
                entry += curr.key + " -> " + "nil" + (cnt - 1) + ";\n";
            }
            if(curr.right == this.nil){
                entry += curr.key + " -> " + "nil" + cnt + ";\n";
            }
            // Move to the right child of the leftmost node
            curr = curr.right;
            // Repeat the process for the right subtree till stack is not empty
        }
        // Add the nil node to rightmost node
        entry += "nil" + cnt + "[label=\"NIL\" shape = record color=black fontcolor=white style=filled height=0.01 width=0.01]\n";
        entry += "}\n";

        // Write the string to the file and close the file
        try{
            fw.write(entry);
            fw.close();
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Run the command to convert the .dot file to a .png file using Graphviz
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "graph_" + num + ".dot", "-o", "graph_" + num + ".png"});
            p.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }

    // Transplant function to replace one subtree as a child of its parent with another subtree
    private void Transplant(Node u, Node v){
        // If u is the root, make v the root
        if(u.parent == this.nil){
            this.root = v;
        }
        // Else if u is a left child, make v a left child
        else if(u == u.parent.left){
            u.parent.left = v;
        }
        // Else make v a right child
        else{
            u.parent.right = v;
        }
        // Make v's parent same as u's parent
        v.parent = u.parent;
    }

    // Function to delete a node from the tree
    public Node Delete(int key){
        // Search for the node to be deleted
        Node z = this.Search(key);
        // If the node is not found, return null
        if(z == this.nil){
            return null;
        }
        Node y = z; // Node to be deleted
        char y_original_color = y.color; // Store the original color of y
        Node x = null; // Node to be attached to the tree in place of y
        // If z has no left child, replace z with its right child
        if(z.left == this.nil){
            x = z.right;
            this.Transplant(z, z.right);
        }
        // Else if z has no right child, replace z with its left child
        else if(z.right == this.nil){
            x = z.left;
            this.Transplant(z, z.left);
        }
        // Else find the successor of z and replace z with it
        else{
            // Successor is the leftmost node in the right subtree of z
            y = z.right;
            while(y.left != this.nil){
                y = y.left;
            }
            y_original_color = y.color;
            x = y.right;
            // If the successor is not a child of z, replace y with its right child, make y's right child z's right child
            // and make z's right child's parent y
            if(y.parent != z){
                this.Transplant(y, y.right);
                y.right = z.right;
                z.right.parent = y;
            }
            // Replace z with y
            this.Transplant(z, y);
            // Make y's left child z's left child and make z's left child's parent y
            y.left = z.left;
            z.left.parent = y;
            y.color = z.color;
        }
        // If the original color of the deleted node was black, fixup the tree
        if(y_original_color == 'b'){
            // We have to fixup the tree only if x is not the root and x's color is black
            while(x != this.root && x.color == 'b'){
                // If x is a left child
                if(x == x.parent.left){
                    Node w = x.parent.right; // x's sibling
                    // Case 1: If x's sibling w is red
                    if(w.color == 'r'){
                        w.color = 'b';
                        x.parent.color = 'r';
                        this.LeftRotate(x.parent);
                        w = x.parent.right;
                    }
                    // Case 2: If both the children of w are black
                    if(w.left.color == 'b' && w.right.color == 'b'){
                        w.color = 'r';
                        x = x.parent;
                    }
                    // Case 3: If the right child of w is black and the left child of w is red
                    else{
                        if(w.right.color == 'b'){
                            w.left.color = 'b';
                            w.color = 'r';
                            this.RightRotate(w);
                            w = x.parent.right;
                        }
                        // Case 4: If the right child of w is red
                        w.color = x.parent.color;
                        x.parent.color = 'b';
                        w.right.color = 'b';
                        this.LeftRotate(x.parent);
                        x = this.root;
                    }
                }
                // Else if x is a right child
                else{
                    Node w = x.parent.left; // x's sibling
                    // Case 1: If x's sibling w is red
                    if(w.color == 'r'){
                        w.color = 'b';
                        x.parent.color = 'r';
                        this.RightRotate(x.parent);
                        w = x.parent.left;
                    }
                    // Case 2: If both the children of w are black
                    if(w.right.color == 'b' && w.left.color == 'b'){
                        w.color = 'r';
                        x = x.parent;
                    }
                    // Case 3: If the left child of w is black and the right child of w is red
                    else{
                        if(w.left.color == 'b'){
                            w.right.color = 'b';
                            w.color = 'r';
                            this.LeftRotate(w);
                            w = x.parent.left;
                        }
                        // Case 4: If the left child of w is red
                        w.color = x.parent.color;
                        x.parent.color = 'b';
                        w.left.color = 'b';
                        this.RightRotate(x.parent);
                        x = this.root;
                    }
                }
            }
            x.color = 'b';
        }
        z.parent = z.left = z.right = null;
        return z;
    }

    // Main function
    public static void main(String[] args){
        // Create a new Red Black Tree
        RBT tree = new RBT();
        Scanner sc = new Scanner(System.in);
        int num = 1; // Number of .png files
        while(true){
            // Scan the choice
            int choice = sc.nextInt();
            // If choice is 1, insert a new node
            if(choice == 1){
                int key = sc.nextInt();
                boolean flag = tree.Insert(key);
                // If the key already exists, print "Key already exists!"
                if(!flag) System.out.println("Key " + key + " already exists!");
                else System.out.println("Key " + key + " inserted!");
            }
            // If choice is 2, search for a node
            else if(choice == 2){
                int key = sc.nextInt();
                Node node = tree.Search(key);
                // Print the message accordingly
                if(node == tree.nil) System.out.println("Key " + key + " not found!");
                else System.out.println("Key " + key + " found!");
            }
            // If choice is 3, print the inorder traversal of the tree
            else if(choice == 3){
                System.out.print("Inorder: ");
                tree.PrintInorder();
            }
            // If choice is 4, generate the graph of the tree
            else if(choice == 4){
                tree.showGraph(num);
                System.out.println("Graph " + num + " generated!");
                num++;
            }
            // If choice is 5, delete a node
            else if(choice == 5){
                int key = sc.nextInt();
                Node z = tree.Delete(key);
                // Print the message accordingly
                if(z == tree.nil) System.out.println("Key " + key + " not found!");
                else System.out.println("Key " + key + " deleted!");
            }
            // If choice is 6, exit the program
            else if(choice == 6){
                break;
            }
            // Else print "Invalid choice!"
            else{
                System.out.println("Error: Invalid choice " + choice + "!");
            }
        }
        sc.close();
    }
}