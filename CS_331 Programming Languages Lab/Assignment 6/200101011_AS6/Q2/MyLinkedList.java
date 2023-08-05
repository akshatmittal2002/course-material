// MyLinkedList class to store adjacency list of a graph
public class MyLinkedList{
    // Node class to store vertex and weight of an edge
    public class Node{
        public int vertex, weight;
        public Node next;
        // Constructor to initialize Node data structure
        Node(int _vertex, int _weight){
            this.vertex = _vertex;
            this.weight = _weight;
            this.next = null;
        }
    }
    public Node head; // Head of linked list
    // Constructor to initialize MyLinkedList data structure
    MyLinkedList(){
        this.head = null;
    }
    // Function to insert a new node at the beginning of linked list
    public void insert(int vertex, int weight){
        Node newNode = new Node(vertex, weight);
        // If linked list is empty, make new node as head
        if(this.head == null){
            this.head = newNode;
        }
        // Else insert new node at the beginning of linked list
        else{
            newNode.next = this.head;
            this.head = newNode;
        }
    }
}