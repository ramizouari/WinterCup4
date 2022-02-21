## Notations

- For an integer $x$, Let $f(x,p)$ be the multiplicity of $p$ in $x$ (how many times can $x$ be divided by $p$).
- For an array $X,$ Let $f(X,p)=\sum_{x\in X} f(x,p)$ be the sum of multiplicities of $p$ of each element of $X$

## Optimal Strategy

We can note that each player can't divide by $p$ more than $f(X,p)$ times, where $X\in\{A,B\}$ is its respective initial array.

So, The optimal strategy for each player is to iteratively choose the same prime number $p \leq L$ which is the least present on the opponent's array: 

1. Rami will choose a prime number which minimises $f(B,p)$ for prime $p\leq L$ 
2. Yessine will choose a prime number which minimises $f(A,p)$ for prime $p\leq L$

## Winner

Let $p_1,p_2$ be the chosen prime numbers for Rami and Yessine respectively:

Rami will win if and only if $f(B,p_1)\leq f(A,p_2).$ That is equivalent to:
$$
\min_{p\in\mathbb{P},p\leq L}f(A,p) \ge \min_{p\in\mathbb{P},p\leq L}f(B,p)
$$