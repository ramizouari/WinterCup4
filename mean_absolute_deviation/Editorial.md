#### Problem Tutorial: “Mean absolute deviation”

**Problem:** Given an array **a[1..n]** and **q** queries : For each query calculate the mean absolute deviation of **a[l..r]**

**Hint 1:** Try to solve the problem offline.

**Hint 2**: Think about data structures 

**Prerequisite:** Segment Tree

**Explanation:**  

Let **av** the average of the range **[l..r]**. We can split this range into two parts **L** and **G**: 

* **L** : Contains the elements of **a[l..r]** less than **av**. Let **n1** his size.

* **G** : Contains the elements of **a[l..r]** greater or equal than **av**. Let **n2** his size.

The mean absolute deviation **MAD** is calculated as follow : **MAD[l..r] = 1/(r-l+1) * (sum(G) - n1.av + n2.av - sum(L))** 

The problem now is how to split the range into this two parts. This can be solved offline using segment tree.

On each node of this segment tree, we shall maintain two pieces of information:  

* The sum of the elements in the range. 

* The number of the elements inserted in the range.					

First, the segment tree is initialised with zeros. We sort the queries by their averages. Then, for each query **[l..r]**, we update the segment tree with the elements of **a** less than the the average of **a[l..r]**. This can be done using a set containing the elements of **a** and their positions.

Now **sum(L)** and **n1** are calculated, the rest of the elements are calculated as below : 

**sum(G) = sum[l..r]-sum(L)**  — **sum[l..r]** can be calculated using prefix sum

**n2 = r-l+1-n1**

Now we apply the formula of **MAD** shown above to obtain the answer. Don't forget to print the answers as in the order of the input.

Time complexity: **O(qlogn)** 
