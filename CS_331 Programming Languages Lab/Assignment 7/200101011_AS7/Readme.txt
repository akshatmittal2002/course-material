    CS331 Assignment 7

Name: Akshat Mittal
Roll No: 200101011

===================================================================================================
Question 1: Red black tree

Steps to run the code:
    javac RBT.java
    java RBT < sample_input.txt

- Input File Format:
    Each operation should be given in a new line.
    Format for operations are as follows:
        Insert a new key        : 1 <key>
        Search for a key        : 2 <key>
        Print Inorder Traversal : 3
        Generate Graph (.png)   : 4
        Delete a key            : 5 <key>
        Exit                    : 6
- Duplicate keys are not allowed.
- The program will throw error if the input is not in the above format.
- Exit code must be present at the end of the input file.
- The .dot and .png files are generated sequentially, i.e. graph_1.dot, graph_2.dot, etc.