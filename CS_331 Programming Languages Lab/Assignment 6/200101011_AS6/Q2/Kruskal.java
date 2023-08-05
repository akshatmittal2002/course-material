import java.util.Scanner; // for reading input
import java.io.*; // for writing output to file to be read by Graphviz

// Kruskal's algorithm for finding the minimum spanning tree of a graph
class Kruskal{
    // Funtion to print the adjacency list of a graph in Graphviz format
    static void printAdjList(int N, MyLinkedList[] adjList, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_adjlist.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "digraph AdjList{\nnode [shape=record];\nrankdir=LR;\nmain [label=\"";
        for(int i=0; i<N; i++){
            entry += "{" + i + "|<next" + i + ">}";
            if(i != N-1) entry += " | ";
            else entry += "\"];\n";
        }
        int j = 0;
        for(int i=0; i<N; i++){
            String last = "main:next" + i;
            MyLinkedList.Node temp = adjList[i].head;
            while(temp != null){
                j++;
                entry += j + " [label=\"{<this>" + temp.vertex + "|" + temp.weight + "|<next>}\", height=0.01];\n";
                entry += last + " -> " + j + ":this;\n";
                last = j + ":next";
                temp = temp.next;
            }
        }
        entry += "}";
        // Write the string to the file and close the file
        try{
            fw.write(entry);
            fw.close();
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Run the command to convert the .dot file to a .png file using Graphviz
        // and then delete the .dot file
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_adjlist.dot", "-o", "Test_" + testCase + "_adjlist.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_adjlist.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Funtion to print the graph in Graphviz format
    static void printGraph(int N, MyLinkedList[] adjList, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_graph.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "graph Graph{\nrankdir=RL;\nlayout=sfdp;\nnode [shape=circle];\n";
        for(int i=N-1; i>=0; i--){
            MyLinkedList.Node temp = adjList[i].head;
            while(temp != null){
                if(temp.vertex <= i) entry += i + " -- " + temp.vertex + " [label=\"" + temp.weight + "\"];\n";
                temp = temp.next;
            }
        }
        entry += "}";
        // Write the string to the file and close the file
        try{
            fw.write(entry);
            fw.close();
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Run the command to convert the .dot file to a .png file using Graphviz
        // and then delete the .dot file
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_graph.dot", "-o", "Test_" + testCase + "_graph.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_graph.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Funtion to print the minimum spanning tree in Graphviz format
    static void printMST(int N, MyEdgeList.Edge[] mst, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_mst.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "graph MST{\nnode [shape=circle];\nlayout=sfdp;\n";
        for(int i=0; i<N-1; i++){
            entry += mst[i].u + " -- " + mst[i].v + " [label=\"" + mst[i].w + "\"];\n";
        }
        entry += "}";
        // Write the string to the file and close the file
        try{
            fw.write(entry);
            fw.close();
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Run the command to convert the .dot file to a .png file using Graphviz
        // and then delete the .dot file
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_mst.dot", "-o", "Test_" + testCase + "_mst.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_mst.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Funtion to print the graph with the minimum spanning tree in Graphviz format
    static void printGraphWithMST(int N, MyLinkedList[] adjList, MyEdgeList.Edge[] mst, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_graph_with_mst.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "strict graph Graph{\nrankdir=RL;\nlayout=sfdp;\nnode [shape=circle];\n";
        for(int i=N-1; i>=0; i--){
            MyLinkedList.Node temp = adjList[i].head;
            while(temp != null){
                if(temp.vertex <= i) entry += i + " -- " + temp.vertex + " [label=\"" + temp.weight + "\"];\n";
                temp = temp.next;
            }
        }
        for(int i=0; i<N-1; i++){
            entry += mst[i].u + " -- " + mst[i].v + " [label=\"" + mst[i].w + "\", color=red];\n";
        }
        entry += "}";
        // Write the string to the file and close the file
        try{
            fw.write(entry);
            fw.close();
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Run the command to convert the .dot file to a .png file using Graphviz
        // and then delete the .dot file
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_graph_with_mst.dot", "-o", "Test_" + testCase + "_graph_with_mst.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_graph_with_mst.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Implementation of Kruskal's algorithm
    static void kruskalAlgo(int N, MyLinkedList[] adjList, MyEdgeList edgeList, int testCase){
        int num = 0; // Number of edges in the MST
        // Create a Union-Find data structure to keep track of the connected components
        UnionFind uf = new UnionFind(N);
        // Create an EdgeList to store the edges in the MST
        MyEdgeList.Edge[] mst = new MyEdgeList.Edge[N-1];
        int totalWeight = 0; // Total weight of the MST
        while(num < N-1){
            // Extract the edge with the minimum weight
            MyEdgeList.Edge temp = edgeList.extractMin();
            if(temp == null) break;
            int u = temp.u;
            int v = temp.v;
            int w = temp.w;
            // Check if the edge connects two different connected components, if yes then add it to the MST
            if(uf.find(u) != uf.find(v)){
                mst[num] = temp;
                uf.union(u, v);
                num++;
                totalWeight += w;
            }
        }
        // If the number of edges in the MST is N-1 then print the MST, else print that the MST does not exists
        // Because if the MST exists then it will have N-1 edges
        if(num == N-1){
            System.out.println("Test #" + testCase + ": Total Weight of MST = " + totalWeight);
        }
        else{
            System.out.println("Test #" + testCase + ": MST does not exists!");
        }
        // Print the adjacency list, graph, MST and graph with MST in Graphviz format
        printAdjList(N, adjList, testCase);
        printGraph(N, adjList, testCase);
        printMST(N, mst, testCase);
        printGraphWithMST(N, adjList, mst, testCase);
    }
    // Main function
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        // Scan all the inputs
        int T = scan.nextInt();
        for(int _i=0; _i<T; _i++){
            int N = scan.nextInt();
            int E = scan.nextInt();
            int u, v, w;
            // Create the adjacency list as well as the edge list
            MyLinkedList[] adjList = new MyLinkedList[N];
            MyEdgeList edgeList = new MyEdgeList(E);
            for(int i=0; i<N; i++){
                adjList[i] = new MyLinkedList();
            }
            for(int i=0; i<E; i++){
                u = scan.nextInt();
                v = scan.nextInt();
                w = scan.nextInt();
                adjList[u].insert(v, w);
                adjList[v].insert(u, w);
                edgeList.insert(u, v, w);
            }
            // Call the Kruskal's algorithm
            kruskalAlgo(N, adjList, edgeList, _i);
        }
    }
}