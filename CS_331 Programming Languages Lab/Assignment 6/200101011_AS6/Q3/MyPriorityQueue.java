// Priority Queue implementation using Min Heap to store the vertices of the graph and their distances from the source vertex
public class MyPriorityQueue{
    private int N; // Maximum number of vertices
    private int[][] heap; // Min Heap to store the vertices and their distances from the source vertex
    private int size; // Current size of the heap
    // Constructor to initialize the heap
    MyPriorityQueue(int _N){
        this.N = _N;
        this.heap = new int[_N][2];
        this.size = 0;
    }
    // Function to get parent of a node
    private int parent(int i){
        return (i-1)/2;
    }
    // Function to get left child of a node
    private int left(int i){
        return 2*i + 1;
    }
    // Function to get right child of a node
    private int right(int i){
        return 2*i + 2;
    }
    // Function to swap two nodes
    private void swap(int i, int j){
        int[] temp = this.heap[i];
        this.heap[i] = this.heap[j];
        this.heap[j] = temp;
    }
    // Function to insert a new node into the heap
    public void insert(int d, int v){
        // If the heap is full, print an error message and return
        if(this.size == this.N){
            System.out.println("Heap is full");
            return;
        }
        // Insert the new node at the end of the heap
        int i = this.size;
        this.size++;
        this.heap[i][0] = d;
        this.heap[i][1] = v;
        // Apply heapify procedure to the heap to maintain the min heap property
        while(i != 0 && this.heap[parent(i)][0] > this.heap[i][0]){
            swap(i, parent(i));
            i = parent(i);
        }
    }
    // Function to get the minimum distanced node from the heap
    public int[] extractMin(){
        // If the heap is empty, return null
        if(this.size <= 0){
            return null;
        }
        // If the heap has only one node, return it
        if(this.size == 1){
            this.size--;
            return this.heap[0];
        }
        // Minimum node is always at the root of the heap
        int[] root = this.heap[0];
        // Replace the root node with the last node in the heap
        this.heap[0] = this.heap[this.size-1];
        this.size--;
        // Apply heapify procedure to the heap to maintain the min heap property
        int i = 0;
        while(i < this.size){
            int l = left(i);
            int r = right(i);
            int smallest = i;
            if(l < this.size && this.heap[l][0] < this.heap[i][0]){
                smallest = l;
            }
            if(r < this.size && this.heap[r][0] < this.heap[smallest][0]){
                smallest = r;
            }
            if(smallest != i){
                swap(i, smallest);
                i = smallest;
            }
            else{
                break;
            }
        }
        // Return the minimum node
        return root;
    }
    // Function to decrease the distance of a node in the heap
    public void decreaseKey(int d, int v){
        int i = 0;
        // Find the node with the given vertex number
        for(i=0; i<this.size; i++){
            if(this.heap[i][1] == v){
                break;
            }
        }
        // If the node is not found, print an error message and return
        if(i == this.size){
            System.out.println("Error: Vertex " + v + " not found");
            return;
        }
        // Decrease the distance of the node
        this.heap[i][0] = d;
        // Apply heapify procedure to the heap to maintain the min heap property
        while(i != 0 && this.heap[parent(i)][0] > this.heap[i][0]){
            swap(i, parent(i));
            i = parent(i);
        }
    }
    // Function to check if the heap is empty
    public boolean isEmpty(){
        return this.size == 0;
    }
}