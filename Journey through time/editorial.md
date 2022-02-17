This Problem can be solved using a greedy algorithm.

Let's start by denoting a node "good" if the subtree of that node contains at least one special node.
It is then trivial that we should only traverse good nodes and ignore the others.
Let's pre-compute the maximum value among the good nodes for each subtree.
The key observation in this problem is that we should prioritize visiting the nodes with the biggest pre-computed value. 
Another important observation is that we should make each traversal as long as possible. 
Therefore, we should stop only when there are no good nodes left.
We can keep track of the unvisited nodes in a max heap (to insure the nodes with largest values are visited first) 
and then we can traverse them using a greedy version of Depth-First search (we visit the nodes with a larger pre-computed value first)

The solution is the sum of the pre-computed values of every node from the max heap from which we initiated a DFS.

Complexity: O(NlogN)