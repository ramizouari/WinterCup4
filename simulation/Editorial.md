# Editorial

## Notation

For $n\in\mathbb{N},\bold{p}\in\mathbb{R}_+^n/ \lVert \bold{p}\rVert_1=\sum_{i=1}^np_i=1,$ we will denote by $\mathcal{M}(m,n,\bold{p})$ the multinomial distribution with parameters $m,n,\bold{p}$.

Let $\bold{A}(n,m)=(\bold{A}(n,m)_1,\dots,\bold{A}(n,m)_{n})$ be the content of a simulation with an array of size $n$ and $m$ iterations.

Let $\bold{X}(n,m)$ be the maximum number for a simulation of size $n$ and $m$ iterations:   
$$
\bold{X}(n,m)=\max_{i\in\{1,\dots,n\}} \bold{A}(n,m)_{i}
$$
We can verify that the problem is equivalent to finding:
$$
\mathcal{P}(\bold{X}(n,m) \ge K)
$$
If $K>m,$ it is trivial that this probabillity is $0.$

Otherwise, we will solve the problem using the law of Total Probability and Dynamic Programming. 

## Observation with $K\leq m:$

We can verify that $\bold{A}(n,m)\sim \mathcal{M}(m,n,\frac{1}{n}\mathbb{1}_n)$ where $\mathbb{1}_n =(1,\dots,1)$ is the vectors of ones.

This observation is the key to finding the formula.

## DP Formula with $K\leq m:$

We have:
$$
\begin{align}
\mathcal{P}(\bold{X}(n,m)\ge K)
&=\sum_{j=0}^{m} \mathcal{P}(\bold{X}(n,m)\ge K  \mid \bold{A}(n,m)_n=j)\times\mathcal{P}(\bold{A}(n,m)_n=j)\\
&=\sum_{j=0}^{K-1} \mathcal{P}(\bold{X}(n,m)\ge K  \mid \bold{A}(n,m)_n=j)\times\mathcal{P}(\bold{A}(n,m)_n=j)\\
&+\sum_{j=K}^{m} \mathcal{P}(\bold{X}(n,m)\ge K  \mid \bold{A}(n,m)_n=j)\times\mathcal{P}(\bold{A}(n,m)_n=j)\\
&=\sum_{j=0}^{K-1} \mathcal{P}(\bold{X}(n-1,m-j)\ge K  )\times\mathcal{P}(\bold{A}(n,m)_n=j)+\sum_{j=K}^{m}\mathcal{P}(\bold{A}(n,m)_n=j)\\
&=\sum_{j=0}^{K-1} {m \choose j}\frac{(n-1)^{m-j}}{n^m} \mathcal{P}(\bold{X}(n-1,m-j)\ge K  )+\sum_{j=K}^{m}{m \choose j}\frac{(n-1)^{m-j}}{n^m}\\
&=\sum_{j=0}^{m} {m \choose j}\frac{(n-1)^{m-j}}{n^m} -\sum_{j=0}^{K-1}{m \choose j}\frac{(n-1)^{m-j}}{n^m}\left(1-\mathcal{P}(\bold{X}(n-1,m-j)\ge K  )\right)\\
&=1-\sum_{j=0}^{K-1}{m \choose j}\frac{(n-1)^{m-j}}{n^m}\left(1-\mathcal{P}(\bold{X}(n-1,m-j)\ge K  )\right)
\end{align}
$$
By denoting $p_{n,m}=\mathcal{P}(\bold{X}(n,m)\ge K),$ we will get this formula:
$$
\boxed{p_{n,m}=1-\sum_{j=0}^{K-1}{m \choose j}\frac{(n-1)^{m-j}}{n^m}\left(1-p_{n-1,m-j}\right)}
$$

## Conclusion

- If $K>m,$ the probability is trivially $0$ 
- The probability is then $p_{n,m}$
- 

## Remarks

To avoid floating point errors, It is best to calculate this formula for the $(n,m)$ iteration as:

```c++
p[n][m] = 1;
long double alpha=static_cast<long double>(n-1)/n;
for(int j=0;j<K;j++)
    p[n][m]-=nCr[m][j]*std::pow(n-1,-j)*std::pow(alpha,m)*(1-p[n-1][m-j])
```

where the type of ``nCr[n][m]`` is ``long doublel``

## Complexity


$$
\mathcal{O}\left(nmK\right)
$$

