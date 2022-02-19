# Editorial

## Prerequisites:

1. Basic finite group theory
2. Linear algebra
3. Basic finite field theory
4. Ring Theory, or otherwise Matrix arithmetic

For this problem, the calculation of the period can be easier when knowing the explicit formula of $(u_n)_{n\in\mathbb{N}}$ and consequently $(v_n)_{n\in\mathbb{N}}$

## Notation

We will denote by $\mathbb{F}_p=\mathbb{Z}/p\mathbb{Z}$ the cyclic field with $p$ elements.

- Let $A=\begin{pmatrix}0&1 \\ b &a\end{pmatrix},$ and $B=A-I_2$ where $I_2$ is the $2\times 2$ identity matrix

- Let $\omega(n)$ be the number of distinct prime factors of an integer $n$

- Let $\Omega(n)$ be the number of prime factors of an integer $n,$ counting multiplicities  

## Observations:

- $(u_n)_{n\in\mathbb{N}}$ and $(v_n)_{n\in\mathbb{N}}$  can be considered as sequences over $\mathbb{F}_p$

- Let $U_n=\begin{pmatrix}u_n \\ u_{n+1}\end{pmatrix},$ we have $U_n=A^nU_0$

- Let  $V_n=\begin{pmatrix}v_n \\ v_{n+1}\end{pmatrix},$ we have:
  $$
  \boxed{V_n=\sum_{k=0}^nU_k=\left(\sum_{k=0}^nkA^k\right)U_0}
  $$
  
- 

The problem is thus reduced to the calculation of: 
$$
\boxed{S_n=\sum_{k=0}^nkA^k}
$$


## Offset Problem

The sequence $(v_n)_{n\in\mathbb{N}}$ is always eventually periodic, but we need to know a choice of offset from which the sequence will be periodic.

The answer is we can always take $K=1.$ The proof is case specific:

1. If $a=b = 0,$ then $v_n=v_1\ \forall n\ge 1$

2. If $a\neq 0$ and $b=0,$ $(u_{n+1})_{n\in\mathbb{N}}$ is a geometric sequence with parameter $a\neq 0,$ which implies 
   $$
   (v_n)_{n\in\mathbb{N}} \ /v_n=\sum_{k=0}^nku_k=\sum_{k=1}^nku_k \text{ is periodic}
   $$
   As $(v_n)_{n\in\mathbb{N}}$ is periodic, $N=0$

3. Otherwise, $b\neq 0:$ we have $A\in\mathtt{GL}_2(\mathbb{F}_p),$ but $\mathtt{GL}_2(\mathbb{F}_p)$ is a finite group under matrix multiplication. So by Lagrange's theorem, the sequence $(A^n)_{n\in\mathbb{N}}$ is periodic.

   Therefore, $(V_n)$ is periodic, so necessarily, $(v_n)$ must be periodic.

   From which we can conclude that $K=0$

As for each case $K\in\{0,1\},$ we can safely choose $1$ as an offset   

## Calculation of $(v_n)_{n\in\mathbb{N}}$

We will consider many cases:

1.  If $p\in\{2,3\},$ then, we may prove that $T=72$ is always an eventual period, So we may calculate the first $T+K$ terms of the sequence, from which we can deduce all the others.

2. Otherwise, if $B$ is invertible, then:
   $$
   \boxed{\forall n\in\mathbb{N},\quad S_n=\sum_{k=0}^n kA^k= \frac{nA^{n+2}-(n+1)A^{n+1}+A}{(A-I_2)^2}=B^{-2}\left(nA^{n+2}-(n+1)A^{n+1}+A\right)}
   $$
   
3.  Otherwise, if $B$ has two eigenvalues $0$ and $\alpha\neq 0$:
   $$
   \boxed{\forall n\in\mathbb{N}, \quad S_n = \frac{n(\alpha+1)^{n+2}-(n+1)(\alpha+1)^{n+1}+\alpha+1}{\alpha^3}B+\frac{n(n+1)}{2}\left(I_2-\alpha^{-1}B\right)}
   $$

4. Otherwise, $B^2=0,$ and we have:
   $$
   \boxed{\forall n\in\mathbb{N}\quad S_n=\frac{n(n+1)(2n+1)}{6}B+\frac{n(n+1)}{2}I_2}
   $$

5.  

## Eventual Period of $(v_n)_{n\in\mathbb{N}}:$ Robustness Index

As we know the formula of $(v_n)_{n\in\mathbb{N}}$ for each case, we can prove that:
$$
R \mid p^2(p^2-p)(p^2-1)
$$
Actually, $R_0=p^2(p^2-p)(p^2-1)$ is a period of $(v_n)_{n\in\mathbb{N}},$ which is actually a "bad" initial guess.  Actually we can prove that:
$$
R \quad\text{divides} \begin{cases}
72 &\text{if }p\in\{2,3\}\\
p(p^2-1) &\text{otherwise}
\end{cases}
$$
Now as we know the initial guess $R_0$ of $R.$ We can choose $m$ random points $t_1,\dots,t_m\ge N.$

Now we iterate over all divisors of $R_0,$ and we find the smallest divisor $R'$ such that:
$$
\boxed{\forall k\in\{1,\dots,m\},\quad v_{t_i+R'}=v_{R'}}
$$
  It is almost surely that:
$$
R=R'
$$

## Complexity

Let $N_{*}=\max_{i\in\{1,\dots,s\}} n_i, $ and $N$ is the largest term used by the periodicity check.

The complexity of this solution on the worst case is:
$$
\mathcal{O}\left(s\log N_*+m\omega(R_0)\Omega(R_0)\log N+ \sqrt p\right)=\mathcal{O}\left(s\log N_*+m\frac{\log N(\log R_0 )^2}{\log \log R_0}+ \sqrt p\right)
$$

Where $R_0$ the initial guess of the fundamental period. Note that $R_0$ must be itself a period of $(v_n)_{n\in\mathbb{N}}$ . 

As the behavior of prime numbers is statistically random, the complexity of this solution may be closer to the average case which is:
$$
\mathcal{O}\left(s\log N_*+m\omega(R_0)\Omega(R_0)\log N+ \sqrt p\right)=\mathcal{O}\left(s\log N_*+m\log N (\log \log R_0)^2+ \sqrt p\right)
$$


## Notes

There is a more advanced solution using Galois Extensions and the Jordan Normal Form.

It has the same time complexity as the solution described here, but it has lower constant factor

Furthermore, the proof that $R \ \text{divides} \begin{cases}
72 &\text{if }p\in\{2,3\}\\
p(p^2-1) &\text{otherwise}
\end{cases}$  is achieved using this solution.

There is also a proof that $(v_n)_{n\in\mathbb{N}}$ satisfies a linear homogeneous recurrence relation of order $5.$ Thus, instead of comparing $m$ random points, we can only compare the first $5$ values, and this solution is deterministic. Its complexity is:
$$
\mathcal{O}\left(s\log N_*+\omega(R_0)\cdot\Omega(R_0)\log N+ \sqrt p\right)=\mathcal{O}\left(s \log N_*+\frac{\log N(\log R_0 )^2}{\log \log R_0}+ \sqrt p\right)
$$
The average case is then:
$$
\mathcal{O}\left(s\log N_*+m\omega(R_0)\Omega(R_0)\log N+ \sqrt p\right)=\mathcal{O}\left(s\log N_*+\log N (\log \log R_0)^2+ \sqrt p\right)
$$


All solutions with all proofs are described formally on the PDF. 