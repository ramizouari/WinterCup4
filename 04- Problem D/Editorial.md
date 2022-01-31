#### Problem Tutorial: “Decrypting the password”

**Problem:** Given a string of digits, count the number of substrings divisible by 11.

**Hint:** A number is divisible by 11 if the sum of even digits subtracted by the sum of odd digits is divisible by 11.

**Explanation:**  

First of all, let's multiply the digits in odd positions by -1

A simple solution is to consider all subarrays one by one and check if sum of every subarray is equal to 0 modulo 11 or not. The complexity of this solution would be **O(n^2)**. 

A better approach is to use dynamic programming.

Let's define the array **sum**, the prefix sum of the digits in the array modulo 11.

For each **1 <= i <= n** , we need to calculate the number of substrings ending in **i** which are divisible by 11 and then print their sum. Formally, we need to find how many **j** **(1 <=j <= i)** exist such that sum[i]  = sum[j] so that **s[j+1..i]** is divisible by 11. 

We solve this with DP. First, we define **dp[x] (0 <= x < 11)** as how many prefix sum (modulo **11**) is equal to **x**.	

To calculate that, for each iteration **i** we simply add **dp[sum[i]]** to the answer and increment **dp[sum[i]]** by **1**.

Time complexity: **O(n)** 
