// UnionFind class to check if including an edge in MST will cause a cycle
public class UnionFind {
    // Node class to store parent and rank of a node
    public class Node {
        public int parent;
        public int rank;
        // Constructor to initialize Node data structure
        Node(int _parent, int _rank){
            this.parent = _parent;
            this.rank = _rank;
        }
    }
    private Node[] nodes; // Array of nodes
    // Constructor to initialize UnionFind data structure
    UnionFind(int _N){
        this.nodes = new Node[_N];
        for(int i=0; i<_N; i++){
            // Initially, all nodes are their own parent and have rank 0
            this.nodes[i] = new Node(i, 0);
        }
    }
    // Function to find the parent of a node
    public int find(int i){
        if(this.nodes[i].parent != i){
            this.nodes[i].parent = find(this.nodes[i].parent);
        }
        return this.nodes[i].parent;
    }
    // Function to union of two nodes
    public void union(int x, int y){
        int xRoot = find(x);
        int yRoot = find(y);
        // If both nodes have same parent, they are already in same set
        if(this.nodes[xRoot].rank < this.nodes[yRoot].rank){
            this.nodes[xRoot].parent = yRoot;
        }
        // Else merge the two sets
        else if(this.nodes[xRoot].rank > this.nodes[yRoot].rank){
            this.nodes[yRoot].parent = xRoot;
        }
        else{
            this.nodes[yRoot].parent = xRoot;
            this.nodes[xRoot].rank++;
        }
    }
}
