#### Problem Tutorial: “Decrypting the password”

**Problem:** Given a string of digits, count the number of substrings divisible by 11.

**Hint:** A number is divisible by 11 if the sum of even digits subtracted by the sum of odd digits is divisible by 11.

**Explanation:**  

First of all, let's multiply the digits in odd positions by -1

A simple solution is to consider all substrings one by one and check if sum of every substring is equal to 0 modulo 11 or not. The complexity of this solution would be $O(n^2)$. 

A better approach is to use dynamic programming.

Let's define the array **$sum$**, the prefix sum of the digits in the array modulo 11.

For each **$1 \le i \le n $** , we need to calculate the number of substrings ending in **$i$** which are divisible by 11 and then print their sum. Formally, we need to find how many **$1\le j \le i$** exist such that $sum[i]  = sum[j]$ so that **$s[j+1..i]$** is divisible by $11$. 

We solve this with DP. First, we define **$dp[x] \ (0 \le x < 11)$** as how many prefix sum (modulo **11**) is equal to **x**.	

To calculate that, for each iteration **$i$** we simply add **$dp[sum[i]]$** to the answer and increment **$dp[sum[i]]$** by **$1$**.

Time complexity: **$O(n)$** 

**Bonus** : 

1. Solve this problem with any prime number $p \leq  10^5$ 

2. Solve this problem with any number $p\leq 10^5$ co-prime with $10.$
3. Solve this problem for any integer $p\leq 10^5$ 
