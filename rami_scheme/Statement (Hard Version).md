# Rami's Scheme

*** Rami ***  always was fond of random numbers, he always wonders how randomness arises from the deterministic nature of mathematics.

Wanting to impress his friends, he created a new pseudo-random number generation scheme, that he proudly called **Rami** Scheme

a *** Rami scheme *** consists of the following steps:

1. choose 4 integer parameters: $m,a,b$  such that $0\leq a,b,<m$  with $m$ prime 

2. choose 2 seeds $0\leq u_0,u_1 <m$ 

3. for $k>1,$ $u_k$ will be generated with the following rule:
   $$
   u_k=(au_{k-1}+bu_{k-2})\bmod m
   $$

4. using the rule above, he will calculate many such numbers and use them to generate the following random numbers $(v_k)_{k\in\mathbb{N}}$:
   $$
   v_k=\left(\sum_{i=0}^kiu_i\right)\bmod m
   $$

5. Finally, after calculating many terms $v_0,\dots,v_{10^{18}},$ he will choose $s$ numbers $v_{n_1},\dots,v_{n_s}.$ those final numbers will be the chosen random numbers  



**Rami** wants you to test his scheme, so he asks you for help.

- First of all, he wants you to measure the robustness index $R$  of this scheme, which is defined as the eventual fundamental period of the sequence $(v_k)_{k\in\mathbb{N}}.$ In other words,he wants the smallest strictly positive integer $R$ such that:

$$
\exists N\in\mathbb{N}/\quad\forall k\in\mathbb{N}_{\ge N}, v_{k+R}=v_k
$$

- After calculating $R$, **Rami** wants you to calculate the periodicity offset index $N$ of this scheme, which is defined as the first index from which the sequence $(v_k)$ will become periodic. In other words, he wants the smallest positive integer $N$ such that:
  $$
  \forall k\in\mathbb{N}_{\ge N},v_{k+R}=v_k
  $$

- After that, he knows that he cannot calculate all terms of the sequence $(v_k)_{k\in\mathbb{N}}$, and he only needs $s$ terms $v_{n_1},\dots,v_{n_s}$ of the sequence. So he asks your help for it

## Input

1. The first line contains $6$ integers, $m,a,b,u_0,u_1,s$: 
   1. $m,a,b:$ the parameters of the scheme
   2. $u_0,u_1:$ the seeds
   3. $s:$ the number of terms to calculate
2. the second line contains $s$ integers, $n_1,\dots,n_s$ representing the terms to calculate  

## Output

1. The first line contains two integers $R,N:$ 
   1. $R: $ the robustness index of the selected scheme
   2. $N:$ the periodicity offset index of the selected scheme

2. The second line contains $s$ integers $v_{n_1},\dots,v_{n_s}:$ the calculated terms 

## Constraints

| $1\leq$ |        $m$        | $\leq 10^9$    |
| ------: | :---------------: | -------------- |
| $1\leq$ |   $a,b,u_0,u_1$   | $< m$          |
| $1\leq$ |        $s$        | $\leq 10^6$    |
| $1\leq$ | $n_1,\dots,n_{s}$ | $\leq 10^{18}$ |

## Time Constraint

$5$ seconds



## Notes

- A prime number is a number whose only divisors are $1$ and itself.
- It can be proven that the sequence $(v_k)_{k\in\mathbb{N}}$ is always eventually periodic.
