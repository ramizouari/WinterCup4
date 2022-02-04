# Simulation

**Rami** and **Oussama** frequently talk about simulations.

> Insert Story here

**Oussama** is doing a simulation:

Given an array $A$ of size $n$ initially filled with zeros, they will do $m$ times these two steps

1. Select a number $k$ uniformly in $\{1,\dots n\}$
2. Increment $A_k$ by $1$

After finishing the simulation, **Oussama** wanted **Rami** to guess the probability that all elements of $A$ are less than a given number $K.$

As the question is a little bit hard, **Oussama**  wanted to ease it and gave **Rami** the value of the first $s$ elements of $A:$ $A_1,\dots,A_s.$

Now, **Rami** was given a simulation of $m$ steps on an array $A$ of size $n$ and a threshold $K,$ and he knows the values of $A_1,\dots,A_s.$ He must correctly guess the probability that all elements of $A$ are less than $K.$

**Rami** is completely stuck, so he asked your help about it.

As the probability is a rational number $\frac{p}{q},$ he wanted you to give him $p\cdot r \bmod (10^{9}+7)$ where  $r$ is the modular inverse of $q,$ In other words:
$$
qr \equiv 1 \ (\bmod10^9+7)
$$


## Input

1. The first line contains $4$ integers: $n,m,K,s$ where:
   - $n:$ the size of the array $A$
   - $m:$ number of steps of the simulation
   - $K:$ the threshold
   - $s:$ number of given elements
2. The second line contains $s$ integers

It is guaranteed that there exists at least one simulation that after $m$ steps, will have the values $A_1,\dots,A_s$ on the first $s$ elements of $A$

## Output

an integer $d:$ the probability that all elements of $A$ are less than $K$ after $m$ steps of the simulation knowing the values of $A_1,\dots,A_s$

## Constraints

| $1 \leq$ |        $n$        | $300$         |
| -------: | :---------------: | ------------- |
| $1 \leq$ |        $m$        | $300$         |
|      $0$ |        $K$        | $\leq 10^{6}$ |
|  $0\leq$ |        $s$        | $\leq n$      |
|  $0\leq$ |  $A_1,\dots,A_s$  | $\leq m$      |
|  $0\leq$ | $\sum_{i=1}^sA_i$ | $\leq m$      |

## Time Constraint

$3$ seconds

## Notes

It can be proven that the probability $p$ is always a rational number