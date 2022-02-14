## Non-Increasing Dilemma

You are given an array $a_1,a_2,…,a_n$ 

You have to perform this operation on the array any number of times : 

* Choose an integer $i$  $(1 \le i \le n)$ and for all $j \ne i$  add $a[i]$ to $a[j]$

What is the minimum number of operations to make the array sorted in non-increasing order?

### Input : 

Each test contains multiple test cases. The first line contains a single integer $t$ $(1\le t \le 10^5)$ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $n$ $(1\le n \le 10^5)$ — the length of the array.

The second line of each test case contains $n$ integers $a_1,a_2,…,a_n$ $(1 \le a_i \le 10^9)$ — the elements of the array.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2⋅10^5$.

### Output : 

For each test case, print one integer $k$ —  The minimum number of operations to make the array sorted in non-increasing order.
