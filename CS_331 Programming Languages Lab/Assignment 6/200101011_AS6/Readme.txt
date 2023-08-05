    CS331 Assignment 6

Name: Akshat Mittal
Roll No: 200101011

===================================================================================================
Question 1.

Steps to run the code:
    javac Form.java
    java Form

- The entries in the form are validated and is stored in the file "Database.txt".

===================================================================================================
Question 2.

Steps to run the code:
    javac Kruskal.java
    java Kruskal < sample_input_Q2.txt

- For each test case, the output is the weight of the MST along with 4 png files:
        1. Test_i_adjlist.png - Adjacency list of the graph
        2. Test_i_graph.png - Graph
        3. Test_i_mst.png - MST of the graph
        4. Test_i_graph_with_mst.png - Graph along with edges of MST highlighted in red

- Files:
        1. Q2.java - Main file
        2. MyEdgeList.java - Implementation of a class EdgeList to store edges and retrieve them in sorted order.
        3. MyLinkedList.java - Implementation of a class LinkedList to store Adjacency list of the graph.
        4. UnionFind.java - Implementation of a class UnionFind to perform union and find operations
                            in order to check for a cycle in the graph.
        5. sample_input_Q2.txt - Sample input file

===================================================================================================
Question 3.

Steps to run the code:
    javac Dijkstra.java
    java Dijkstra < sample_input_Q3.txt

- For each test case, the output is the weight of shortest path from source to destination along with 4 png files:
        1. Test_i_adjlist.png - Adjacency list of the graph
        2. Test_i_graph.png - Graph
        3. Test_i_shortest_path.png - Shortest path from source to destination
        4. Test_i_graph_with_shortest_path.png - Graph along with edges of shortest path highlighted in yellow,
                                                source in green and destination in red.

- Files:
        1. Q3.java - Main file
        2. MyLinkedList.java - Implementation of a class LinkedList to store Adjacency list of the graph.
        3. MyPriorityQueue.java - Implementation of a class PriorityQueue to store vertices and retrieve them in order of distance.
        4. sample_input_Q3.txt - Sample input file