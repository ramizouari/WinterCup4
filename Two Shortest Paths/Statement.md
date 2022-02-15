**Yessine** and **Rami** are living in Sfax. 

Sfax is a rectangular grid of size $n*m$. Each cell has a number written on it, the number on the cell $(i,j)$ is $a_i$ $_j$. 

**Yessine** is living in cell $(1,1)$ and wants to go to the cell $(n,m)$. 

**Rami** is living in cell $(1,m)$ and wants to go to the cell $(n,1)$ 

**Rami** and **Yessine** can move to any other cell cell that share the same edge with his current cell, in other words they can move **UP**, **DOWN**, **LEFT**, or **RIGHT**.

Between all the paths, to reach their destinations, Yessine and Rami take the path that has the minimum sum path including the start cell and the end cell.

The sum path of some path is the sum of all numbers in all cells in this path. 

As **Oussama** is their best friend, he wanted to put on each cell $(i,j)$ **distinct** positive integers such that the sum of the two shortest paths of **Yessine** and **Rami** is minimal as possible.

Oussama is stuck. Please help him determine what is the minimal sum of the two shortest paths.

### Input

The first line contains a single integer $t$  $(1 \le t \le 10000)$ — the number of test cases.

Each test case contains a line of two integers $n$ and $m$ denoting the size of the grid $(2 \le n,m \le 10^4)$

### Output

For each test case, print a single integer $k$  — The minimal sum of the two shortest paths.
