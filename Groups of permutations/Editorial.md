This problem has multiple answers. One of them is using DFS. In this editorial, we use zero-based indexing.

Let's build a graph consisting of $n+1$ nodes. 

There is an edge between node $i$ and $j$ only if $a[i..j-1]$ is a permutation. There is at most $n^2$ edges of them.

There is an answer only if there is a path between node $0$ and node $n$. In other words, node $0$ and node $n$ are in the same component.

To do this, we run a simple DFS from node $0$ and see if we can reach node $n$.

Complexity : $O(n^2)$
