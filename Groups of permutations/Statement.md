## Groups of permutations (UNFINISHED)

```
Input file: 	grp.in
Output file: 	standard output
Balloon Color: 	?
```

Yessine has an array **a** of positive integers.

He wonder if he can partition this array into consecutive groups such that every group is a permutation of any size.

For example, if $a = [4,1,3,2,2,1,3,2,1]$ he can split it into $3$ groups : $([4,1,3,2] \ [2,1] \ [3,2,1])$. However the array $a = [4,1,3,2,3,1]$ can't be partitioned into groups of permutations.

A permutation is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[3,1,2,5,4]$ is a permutation, but $[1,2,1]$ is not a permutation (1 appears twice in the array) and $[2,1,4]$ is also not a permutation ($n=3$, but $4$ is in the array).

#### Input :

The first line of each test case contains one integer $n \ (1≤n≤200)$ — the size of **a** 

The second line contains $n$ positive integers $a_1, a_2, …,\ a_n \ (1≤a_i≤ 200)$  

#### Output :

If there is a solution, print "YES". Otherwise, print "NO"

#### Example:

Input:  

```
9
4 1 3 2 2 1 3 2 1
```

Output:  

```
YES
```

Input:  

```
6
4 1 3 2 3 1
```

Output:  

```
NO
```
