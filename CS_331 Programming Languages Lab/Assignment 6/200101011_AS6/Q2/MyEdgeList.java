// EgdeList class to store edges as a min heap
public class MyEdgeList {
    // Edge class to store a single edge, a node
    public class Edge {
        public int u, v, w;
        // Constructor to initialize Edge data structure
        Edge(int _u, int _v, int _w){
            this.u = _u;
            this.v = _v;
            this.w = _w;
        }
    }
    private int N; // Max size of heap
    private int size; // Current size of heap
    private Edge[] heap; // Array of Edge to store heap
    // Constructor to initialize EdgeList data structure
    MyEdgeList(int _N){
        this.N = _N;
        this.heap = new Edge[_N];
        this.size = 0;
    }
    // Function to get index of parent of node at index i
    private int parent(int i){
        return (i-1)/2;
    }
    // Function to get index of left child of node at index i
    private int left(int i){
        return 2*i + 1;
    }
    // Function to get index of right child of node at index i
    private int right(int i){
        return 2*i + 2;
    }
    // Function to swap two nodes of heap
    private void swap(int i, int j){
        Edge temp = this.heap[i];
        this.heap[i] = this.heap[j];
        this.heap[j] = temp;
    }
    // Function to check if heap is empty
    public boolean isEmpty(){
        return this.size == 0;
    }
    // Function to insert a new edge into heap
    public void insert(int u, int v, int w){
        // If heap is full, return
        if(this.size == this.N){
            System.out.println("Heap is full");
            return;
        }
        // Insert new edge at end of heap
        int i = this.size;
        this.size++;
        this.heap[i] = new Edge(u, v, w);
        // Apply Heapify procedure to fix the min heap property
        while(i != 0 && this.heap[parent(i)].w > this.heap[i].w){
            swap(i, parent(i));
            i = parent(i);
        }
    }
    // Function to extract minimum weight edge from heap
    public Edge extractMin(){
        // If heap is empty, return null
        if(this.size <= 0){
            return null;
        }
        // If heap has only one node, return it
        if(this.size == 1){
            this.size--;
            return this.heap[0];
        }
        // Minimum weight edge is at root always
        Edge root = this.heap[0];
        // Replace root with last node
        this.heap[0] = this.heap[this.size-1];
        this.size--;
        // Apply Heapify procedure to fix the min heap property
        int i = 0;
        while(i < this.size){
            int l = left(i);
            int r = right(i);
            int smallest = i;
            if(l < this.size && this.heap[l].w < this.heap[i].w){
                smallest = l;
            }
            if(r < this.size && this.heap[r].w < this.heap[smallest].w){
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
        return root;
    }
}
