#### Problem Tutorial: “Rami scheme (Easy Version)” 

**Prerequisite:** Binary Search / Z-function

**Explanation:**

Let's start by precomputing the first $2.10^6$ elements of $v$. 

We define $f(i)$, a Boolean function that returns $True$ if

$$
\exists \ k \in \mathbb{N^*} \ , \forall j \ge i \ , v[j+k] = v[j]
$$

And $False$ otherwise.

To calculate $f(i)$ we remove the first $i-1$ elements from $v$ and check if the new sequence is periodic using Z-function.

To calculate the offset $N$, we need to find the smallest $i \ge 0$ such that $f(i) = True$. This will be the value of the offset and it can be calculated using a binary search.

After finding the offset $N$, we remove the first $N$ elements from $v$, let $v'$ this new sequence and $z$ it's Z-function.

The period of $v'$ is equal to the smallest $i \ge 0$ such that $z[i] = 2.10^6-N-i$ . The eventual period of $v$ is the period of $v'$. 

**Bonus:** Prove that the offset can't exceed 1
