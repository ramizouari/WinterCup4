This problem has 2 possible solutions : the first is a greedy algorithm and the second uses flow networks. 
We will discuss the first one since it was the intended solution.

Let R be the sequence of numbers of black cells per row and C the sequence of numbers of black cells per columns. 

We claim that the following strategy always find a solution if it exists:
Greedily Iterate over all the rows, considering at each iteration the row i with the highest value in R first. (This can be implemented using a priority queue).
For each row visited, iterate greedily over all the columns by always considering the column j with the highest value in C first (This also can be implemented using a priority queue). 
When visiting the column j, if R[i]>0 and C[j]>0, decrement both R[i]and C[j] and set M[i][j] to 1, or set i to 0 otherwise .
Notice that after visiting a row i, the values of C will be updated so we will have to construct a new priority queue for C each time we are visiting a new row.  
After iterating over all the rows and columns, all the elements in C and R must be zeroes otherwise we failed to meet the requirements and no solution exists.

Why does this work? Let's prove it.
for a row i, we will have to find at least R[i] columns with a value C[j]>0 thus when updating C we want it to have as few zeroes as possible. Since the number of zeroes in C can't be decreased, we should try to avoid increasing it by avoiding updating element to zeroes This can be done by updating the column with highest value in C each time.
Now that we know why we should always consider the columns with the highest values first, it remains prove that we should always consider the rows with the highest values. It turns out that this is so simple to prove: it is trivial that the number of columns with non-zero values will decrease or remains the same for each iteration over the rows, so delaying the visit to the rows with the highest values might prevent them from finding the required number of columns with non-zero values.

since building a priority queue will take O(NlogN), and we will have to build N prioriy queues (one for each row), the overall complexity of the solution is O(N²logN).