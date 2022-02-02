# Mean Absolute Deviation

**Rami** may loves many branches of mathematics. But, if there is an exception, it must be statistics.

For usual mathematical problems, he will devote his time to understand the structure of the problem and gain intuition, but for statistics, he will forward it to a friend.

But when Statistics and Competitive Programming intersects, that friend should be **Yessine ** who received a recent email from **Rami ** :



> To Yessine
>
> Given $n$ reals $\bold{x}=[x_1,\dots,x_n],$
>
> I challenge you to calculate the mean absolute deviation $\delta(\bold{x})$ (MAD):
> $$
> \delta(\bold{x})=\frac{1}{n}\sum_{i=1}^n\lvert x_i-\mu(\bold{x})\rvert \\
> \text{where: } \mu(\bold{x})=\frac{1}{n}\sum_{i=1}^nx_i \text{ is the mean}
> $$
> Now, to make things worse, I challenge you to redo the calculation for $q$ subarrays of $\bold{x}:\bold{x_{[l_1,r_1]}},\dots,\bold{x_{[l_q,r_q]}}$:
> $$
> \text{Find }\delta(\bold{x}_{[l_i,r_i]}) \text{ for each }i\in\{1,\dots,q\}\\
> \text{Hint:} \quad\delta(\bold{x}_{[l_i,r_i]})=\frac{1}{r_i-l_i+1}\sum_{j=l_i}^{r_i} \lvert x_j-\mu(\bold{x}_{[l_i,r_i]}) \rvert\\
> \text{where }  \mu(\bold{x}_{[l_i,r_i]}) \text{ is the mean of the subarray }\bold{x}_{[l_i,r_i]} 
> $$
> 
>
> 
>
> Best Regards, 
>
> Rami.



**Yessine** was  mad that such an easy problem was given to him, or so he thought until reading the constraints.

Now, neither **Rami** nor **Yessine** are capable of solving this problem, so they both request your help.

## Input

1. The first line contains two integers $n,q$ representing the size of the sample and the number of queries
2. The second line contains $n$ reals $x_1,\dots,x_n$ representing the sample
3. Each of the following $q$ lines contains $2$ integers $l,r$ representing the considered sub-sample 

## Output

$q$ reals. with the $i^\text{th}$ line representing the mean absolute deviation of the subarray $x_{l_i},\dots,x_{r_i}$

## Constraints

| $1 \leq$ | $n,q$ | $\leq 10^5$ |
| -------: | :---: | ----------- |
| $1 \leq$ | $x_i$ | $< 10^3$    |

## Time Constraint

$3$ seconds