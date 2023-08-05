import java.util.Scanner; // for reading input
import java.io.*; // for writing output to file for graphviz

// Implementation of Dijkstra's algorithm
class Dijkstra{
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
    // Function to print the graph in Graphviz format
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
    // Function to print the shortest path in Graphviz format
    static void printShortestPath(int N, int[] par, int[] weight, int S, int D, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_shortestpath.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "graph ShortestPath{\nnode [shape=circle];\nrankdir=RL;\n";
        entry += S + " [color=yellow];\n";
        int cur = D;
        while(cur != S){
            entry += cur + " [color=yellow];\n";
            entry += cur + " -- " + par[cur] + " [label=\"" + weight[cur] + "\", color=red];\n";
            cur = par[cur];
        }
        entry += S + " [color=yellow];\n";
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
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_shortestpath.dot", "-o", "Test_" + testCase + "_shortestpath.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_shortestpath.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Function to print the graph with the shortest path in Graphviz format
    static void printGraphWithShortestPath(int N, MyLinkedList[] adjList, int[] par, int[] weight, int S, int D, int testCase){
        // Create a .dot file to be read by Graphviz
        FileWriter fw = null;
        try{
            fw = new FileWriter("Test_" + testCase + "_graphwithshortestpath.dot", false);
        }catch(IOException e){
            System.out.println("Error: " + e);
            return;
        }
        // Create a string to be written to the file
        String entry = "strict graph GraphWithShortestPath{\nnode [shape=circle];\nlayout=sfdp;\nrankdir=RL;\n";
        for(int i=N-1; i>=0; i--){
            MyLinkedList.Node temp = adjList[i].head;
            while(temp != null){
                if(temp.vertex <= i) entry += i + " -- " + temp.vertex + " [label=\"" + temp.weight + "\"];\n";
                temp = temp.next;
            }
        }
        int cur = D;
        while(cur != S){
            if(cur != D) entry += cur + " [color=yellow];\n";
            entry += cur + " -- " + par[cur] + " [label=\"" + weight[cur] + "\", color=yellow, style=bold];\n";
            cur = par[cur];
        }
        entry += S + " [color=green, style=filled];\n";
        entry += D + " [color=red, style=filled];\n";
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
        try{
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-Tpng", "Test_" + testCase + "_graphwithshortestpath.dot", "-o", "Test_" + testCase + "_graph_with_shortestpath.png"});
            p.waitFor();
            Process p2 = Runtime.getRuntime().exec(new String[]{"rm", "Test_" + testCase + "_graphwithshortestpath.dot"});
            p2.waitFor();
        }catch(IOException | InterruptedException e){
            System.out.println("Error: " + e);
            return;
        }
    }
    // Dijsktra's Algorithm
    static void dijkstraAlgo(int N, MyLinkedList[] adjList, int S, int D, int testCase){
        int[] dist = new int[N]; // Array to store the shortest distance from S to i
        int[] par = new int[N]; // Array to store the parent of i in shortest path tree
        int[] weight = new int[N]; // Array to store the weight of the edge from parent of i to i in shortest path tree
        boolean[] vis = new boolean[N]; // Array to store whether i has been included in the shortest path tree or not
        // Initialize the arrays
        for(int i=0; i<N; i++){
            dist[i] = Integer.MAX_VALUE;
            par[i] = -1;
            weight[i] = Integer.MAX_VALUE;
            vis[i] = false;
        }
        // Set the distance of S to 0
        dist[S] = 0;
        // Create a priority queue to store the vertices in increasing order of their distance from S
        MyPriorityQueue pq = new MyPriorityQueue(N);
        // Insert all the vertices into the priority queue
        for(int i=0; i<N; i++){
            pq.insert(dist[i], i);
        }
        // Run the loop until the priority queue is empty
        while(!pq.isEmpty()){
            // Extract the vertex with minimum distance from S
            int[] u = pq.extractMin();
            // Include the vertex in the shortest path tree
            vis[u[1]] = true;
            // Update the distance of all the adjacent vertices of u
            MyLinkedList.Node temp = adjList[u[1]].head;
            while(temp != null){
                int v = temp.vertex;
                int w = temp.weight;
                // If the vertex is not included in the shortest path tree and the distance of v is greater
                // than the distance of u + weight of edge from u to v
                if(!vis[v] && dist[u[1]] != Integer.MAX_VALUE && dist[v] > dist[u[1]] + w){
                    dist[v] = dist[u[1]] + w;
                    par[v] = u[1];
                    weight[v] = w;
                    // Decrease the key of v in the priority queue
                    pq.decreaseKey(dist[v], v);
                }
                temp = temp.next;
            }
        }
        // Print the weight of the shortest path from S to D
        System.out.print("Test #" + testCase + ": Distance from vertex " + S + " to " + D + " = ");
        if(dist[D] == Integer.MAX_VALUE){
            System.out.println("-1");
        }
        else{
            System.out.println(dist[D]);
        }
        // Print the adjacency list, graph, shortest path and graph with shortest path in graphviz format
        printAdjList(N, adjList, testCase);
        printGraph(N, adjList, testCase);
        printShortestPath(N, par, weight, S, D, testCase);
        printGraphWithShortestPath(N, adjList, par, weight, S, D, testCase);
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
            // Create an array of linked lists to store the adjacency list of the graph
            MyLinkedList[] adjList = new MyLinkedList[N];
            for(int i=0; i<N; i++){
                adjList[i] = new MyLinkedList();
            }
            for(int i=0; i<E; i++){
                u = scan.nextInt();
                v = scan.nextInt();
                w = scan.nextInt();
                adjList[u].insert(v, w);
                adjList[v].insert(u, w);
            }
            // Scan the source and destination vertices
            int S = scan.nextInt();
            int D = scan.nextInt();
            // Run Dijkstra's Algorithm
            dijkstraAlgo(N, adjList, S, D, _i);
        }
    }
}