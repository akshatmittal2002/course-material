
Team No: 7
    - Akshat Mittal, 200101011
    - Pradeep Kumar, 200101080

===================================================================================================
                    Implementation of KMeans and LBG Algorithm
===================================================================================================

Points to note:
- The input dataset should be placed in a file with correct input format.
- First Line of input: A B C D E
    where,  A is number of data points
            B is number of attributes of a point, i.e., dimension
            C is number of clusters (i.e., K for Kmeans and M for LBG)
            D is maximum number of iterations
            E indicates if data points have associated labels or not. '0' for no labels and '1' for labels.
- Next A lines conatins B attributes of data points and a label (if E = 1).
- Euclidean distance is used to calculate distortion.
- The generated clusters and their corresponding data points are printed in the output file.

Steps to run:
    Compile: g++ kmeans.c (or lbg.c)
    Execute: a.exe <input_file> <output_file>