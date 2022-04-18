This problem might look hard at first glance, but it's actually one of the easiest in the problemset. 

Let i be the smallest index such that A[i]>A[i-1]. If such an index exist, we will have to perform the operation in order to make A[i-1]>A[i]. otherwise, the array in already non-increasing so the answer is 0.
The key observation here is to notice that once you do the operation at an index i, you will have to do it for every element in the subarray[i+1..n].
Why is that? The operation consists of adding A[i] to every element in the array other than A[i], since the elements are postive , A[i] will become the smallest element in the array which means A[i+1] is now strictly greater than A[i] hence we will have to apply the operation at index i+1 which will make A[i+1] the smallest element in the array thus we will have to do the operation at index i+2 and so on till we reach the last index.

Time Complexity: O(n)