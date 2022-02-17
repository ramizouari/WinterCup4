This is the easiest problem in the problemset and the solution is rather simple.

First, let's observe that if the last row isn't composed only of characters C then the answer is NO.
Second, let's remark that if the last row contains only the character C, then we can transform every cell of the grid to C.
Thus the solution is really simple: You just need to check that the last row contains only the character C.

There is one edge case when the number of columns is 1 , in this case you need to check if grid already contains the character C only.
If not, then we cannot change the grid and the answer therefore is NO 