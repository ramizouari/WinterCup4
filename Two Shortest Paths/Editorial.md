## Greedy Solution

The solution is to find the longest possible common path between **Rami** and **Yessine** between possible pair of paths that don't go backward.

We will denote by $L$ the length of such common path, it can be proven that: $L=\max(n,m).$

1. We will set the costs of the cells on this common path to $1,\dots,L.$ 
2. We will set the costs on the remaining cells of the pair of paths with the smallest possible remaining distinct values
3. We will set the costs of the remaining cells freely

In the section below, we will prove that this solution is correct.

## Notations

Let $E$ be the set of grids that will be accessed by **Rami**, and $F$ be the set of grids that will be accessed by **Yessine**

- Let $H=E\cap F$ be the intersection of the two paths.
- Let $\mathcal{C}(a)$ be the cost of a cell $a,$ and $\mathcal{C}(X)=\sum_{x\in X} \mathcal{C}(x)$ the cost of a subset $X$ of cells
- Let $\lvert X \rvert $ be the number of elements (cardinality) of a set $X.$
- Let $\mathcal{C}_1$ be the cost of rami's trajectory, and $\mathcal{C}_2$ be the cost of Yessine's trajectory
- We will denote by $X\setminus Y$ the set difference between $X$  and $Y$ 

## Main Observation

- We can prove that **Rami** and **Yessine** will always take $n-1$ vertical steps and $m-1$ horizonal steps each to arrive at the desired destination. Otherwise, the cost won't be optimal.

- So we have:
  $$
  \lvert E\rvert=\lvert F\rvert=n+m-1
  $$
  
- With this knowledge, we can also prove that
  $$
  \begin{align*}\mathcal{C}_1+\mathcal{C}_2&=\mathcal{C}(E)+\mathcal{C}(F)\\
  &=\mathcal{C}(E \setminus H)+\mathcal{C}(F \setminus H)+2\mathcal{C}(H)\\
  \end{align*}
  $$

- 

## Minimising Cost for a given pair of Paths

We will assume that **Rami** and **Yessine** have already chosen a path.

As $E \setminus H,\ F \setminus H,$ and $H$ are all disjoint sets, $\mathcal{C}_1+\mathcal{C}_2$ will be minimised by minimising the costs of elements of $H$ because it has the highest coefficient in the sum.

Therefore:
$$
\mathcal{C}(H)=\sum_{x\in H}\mathcal{C}(x)=\sum_{i=1}^{\lvert H\rvert}i
$$
Now, as $E \setminus H$ and $F \setminus H$  have the same coefficients in the sum, we can freely set the cost of their elements with any distinct values on the range: 
$$
\{\lvert H\rvert+1,\dots,\lvert H\rvert+\lvert E \setminus H\rvert +\lvert F \setminus H\rvert\}=\{\lvert H\rvert+1,\dots,\lvert E \rvert +\lvert F\rvert-\lvert H\rvert\}
$$
With that in hand, it is trivial to prove that:
$$
\mathcal{C}(E \setminus H) +\mathcal{C}(F\setminus H)+\mathcal{C}(H)=\sum_{i=1}^{\lvert E\rvert+\lvert F\rvert-\lvert H\rvert}i=\sum_{i=1}^{\lvert E \cup F\rvert}i
$$
Now, the total cost is:
$$
\begin{align*}\mathcal{C}_1+\mathcal{C}_2&=\mathcal{C}(E \setminus H)+\mathcal{C}(F \setminus H)+2\mathcal{C}(H)\\
&=\sum_{i=1}^{\lvert E\vert +\lvert F\vert -\lvert H\vert }i +\sum_{i=1}^{\lvert H\vert }i\\
&=\sum_{i=1}^{2n+2m-2 -\lvert H\vert }i+\frac{\lvert H\rvert(\lvert H\rvert+1)}{2}\\
&=\frac{(2n+2m-2-\lvert H\rvert)(2n+2m-\lvert H\rvert-1)}{2}+\frac{\lvert H\rvert(\lvert H\rvert+1)}{2}\\
&=\frac{(2n+2m-2)(2n+2m-1)}{2}-\frac{2n+2m+2n+2m-4}{2}\lvert H\rvert +\lvert H \rvert^2 \\
&=\frac{(2n+2m-2)(2n+2m-1)}{2}-(2n+2m-2)\lvert H\rvert+\lvert H \rvert^2\\
&=\frac{(2n+2m-2)(2n+2m-1)}{2}-\lvert H\rvert\left(2n+2m-2-\lvert H\rvert \right)
\end{align*}
$$

## Minimising Cost

We have $C_1+C_2$ is a quadratic function of $\lvert H \rvert.$ But the real quadratic function $x\rightarrow x(2n+2m-1-x)$ is decreasing at the interval $[0,n+m-1].$

Now, as $0\leq \lvert H\rvert \leq \min(\lvert E\rvert ,\lvert F\rvert)=n+m-1,$   $C_1+C_2$ is minimised by maximising $\lvert H \rvert.$

To say it clearer,the paths of **Rami** and **Yessine** must have the greatest number of common grids.

Now, As the friends won't go backward in their trajectory, and assuming $m>n,$ it can be proven that such paths will have $m$ common grids.

By symmetry, $\lvert H\rvert =\max(n,m)$

## Conclusion

Let $r=\lvert E \rvert = \lvert F\vert = n+m-1$
$$
\begin{align*}
\mathcal{C}_1+\mathcal{C}_2&=\frac{(2n+2m-2)(2n+2m-1)}{2}-\max(n,m)\cdot\left(2n+2m-2-\max(n,m) \right)\\
&=r(2r+1)-\max(n,m)\cdot\left(2r-\max(n,m) \right)
\end{align*}
$$

