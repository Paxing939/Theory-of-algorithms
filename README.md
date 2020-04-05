# Theory-of-algorithms
Realization of different tasks and algorithms. Most of it I've done as my University homework.

### Tree task

Find and delete (if there is such a vertex, by right deleting) the maximum value among the vertices for which the distance to any other tree vertex is strictly less than `k` and through which semipaths of length `k` do not pass (the semipath length and the distance between two vertices are measured by the number of arcs).

Input formatL: the first line contains an integer k (0 ≤ k ≤ 109). In the following lines, each with one number, are the keys of the vertices of the source tree (from `0` to `2^31 - 1`) in the order they are added to the tree. The number of vertices is arbitrary - from `0` to `1000`.

Output format: the output file must contain a sequence of vertex keys obtained by direct left traversal of the resulting tree. If as a result the tree was completely deleted, then the message No tree should be output to the output file.

###### Solution - tree_task.cpp

### Matrix Multiplication Order
Given a sequence of `s` matrices `A1, A2, ..., As`. It is required to determine in which order they should be multiplied so that the number of atomic operations of multiplication is minimal. Matrices are assumed to be compatible with respect to matrix multiplication (i.e., the number of columns of the matrix Ai - 1 coincides with the number of rows of the matrix Ai).

We assume that the matrix product is an operation that takes two k × m and m × n matrices as input and returns a k × n matrix, having spent kmn atomic multiplication operations on it. (The basic type allows you to store any element of the final and any possible intermediate matrix, so multiplying two elements requires one atomic operation.)

Since matrix multiplication is associative, the resulting matrix is independent of the order in which the multiplication operations are performed. In other words, there is no difference in what order the brackets are placed between the factors, the result will be the same.

Input format
The first line contains the number s of matrices (2 ≤ s ≤ 100). The next s lines contain the sizes of the matrices: row i + 1 contains, with a space, the number ni of rows and the number mi of columns of the matrix Ai (1 ≤ ni, mi ≤ 100). It is guaranteed that mi coincides with ni + 1 for all indices i from 1 to s - 1.
Output format
Print the minimum number of atomic multiplication operations needed to multiply s matrices.
