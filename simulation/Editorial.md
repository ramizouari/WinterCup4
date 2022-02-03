# Editorial

## Notation

For $n\in\mathbb{N},\bold{p}\in\mathbb{R}_+^n/ \lVert \bold{p}\rVert_1=\sum_{i=1}^np_i=1,$ we will denote by $\mathcal{M}(m,n,\bold{p})$ the multinomial distribution with parameters.

## Observation with $s=0 \ \& \ K\leq m:$

Let $\bold{A}(n,m)=(\bold{A}(n,m)_1,\dots,\bold{A}(n,m)_{n})$ be the content of a simulation with an array of size $n$ and $m$ iterations.

We can verify that $\bold{A}(n,m)\sim \mathcal{M}(m,n,\frac{1}{n}\mathbb{1}_n)$ where $\mathbb{1}_n =(1,\dots,1)$

## DP Formula with $s=0 \ \& \ K\leq m:$

Let $\bold{X}(n,m)$ be the maximum number for a simulation of size $n$ and $m$ iterations:   
$$
\bold{X}(n,m)=\max_{i\in\{1,\dots,n\}} \bold{A}(n,m)_{i}
$$
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
- For $s=0,$ the probability is then $p_{n,m}$
- For $s>0,$ Let $A_1,\dots,A_s$ be the known numbers
  - If $\max A\ge K,$ the probability is trivially $1$
  - Else, Let $n'=n-s,\quad m'=m-\sum_{i=1}^sA_i,$ the solution is: $p_{n',m'}$ 

## Complexity

$$
\mathcal{O}\left(nmK\right)
$$

