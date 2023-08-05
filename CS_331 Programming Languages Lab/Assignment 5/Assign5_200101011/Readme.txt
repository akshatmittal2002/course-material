CS_331 Assignment 5

Name: Akshat Mittal
Roll: 200101011
Allocated: Q.8 (Merge Sort Tree)

Input Format:
    Size_of_Array
    arr1 arr2 arr3 ... arrN
    Number_of_Queries
    <Query i:> L R K

Command to run:
    g++ main.cpp (To compile)
    a.exe        (To run)

Space Complexity Analysis:
    For building the tree, we require a tree array of size 4*N and
    each element of this array is again an array of maximum size N.
    But at each level of tree, there are N elements stored.
    Maximum level possible is O(lg N).
    So, total space required will be O(N*lg N + 4N) = O(N*lg N).

Time Complexity Analysis:
For Building the tree:
    Time to build a tree is equal to time to build both childs (of half size) and merging them.

    T(N) = 2*T(N/2) + O(N)
    using Master's Theorem, T(N) = O(N*lg N)

For a single Query:
    Time to search a tree is equal to time to search a child and use binary search at the node.

    T(N) = T(N/2) + O(lg N)
    using Master's Theorem, T(N) = O(lg N*lg N) = O((lg N)^2)