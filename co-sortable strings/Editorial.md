## Strategy

The strategy is to construct two strings $u,v$ where $u_i=\min(a_i,b_i)$ and $v_i=\max(a_i,b_i).$ Now we will split simultaneously $u$ and $v$ into co-sortable components.

For a query, the two substrings $a_{[l_i \dots r_i]},b_{[l_i\dots r_i]}$ are co-sortable if and only if $u_{[l_i\dots r_i]}$ and $v_{[l_i\dots r_i]}$ are sorted, which can be easily solved by many methods.

In the following section, we will give a formal proof of the correctness of our strategy. Note that the length of the proof is due to its formality, not its difficulty.

## co-Sortable Component

A co-sortable component is a quadruplet $(l,r,a,b)$ such that $a_{[l\dots r]},b_{[l\dots r]}$ are co-sortable.

## $\mathtt{minmax}$ reduction:

Let $x,y,x',y'$ two characters. We have the following:
$$
xy \text{ and } x'y' \text{ are co-sortable} \iff \begin{cases} \min(x,y) \leq \min(x',y') \\ \max(x,y)\leq \max(x',y')\end{cases}
$$
To prove it, we will suppose without a loss of generality, that $x\leq y$

1. If $x'\leq y',$ then the equivalence is immediate.

2. Otherwise, $x'> y'.$ 

   1. Suppose that $xy$ and $x'y'$ are co-sortable, we have:

      $\begin{cases}x \leq x' \\ y\leq y' \end{cases}$   or $\begin{cases}x \leq y' \\ y\leq x' \end{cases} .$  We will prove that the first implies the second:
      $$
      \begin{cases}
      x\leq x'\\
      y\leq y'
      \end{cases} \implies \begin{cases}
      y\leq y' < x'\\
      x\leq y \leq y'
      \end{cases} \implies \begin{cases}
      y \leq x'\\
      x\leq y'
      \end{cases}
      $$
      As a conclusion:
      $$
      \begin{cases}
      \min(x,y) \leq \min(x',y')\\
      \max(x,y)\leq \max(x',y')
      \end{cases}
      $$

   2. Now, suppose that the conclusion just above holds, it is trivial that $xy$ and $x'y'$ are co-sortable. Which completes the proof $\square$.

   Now, by induction, we can prove that:
   $$
   \boxed{\forall\text{strings } a \text{ and }b,  \ a \text{ and }b \text{ co-sortable}\iff \forall i\leq j,\begin{cases}u_i=\min(a_i,b_i)\leq u_j=\min(a_j,b_j)\\v_i=\max(a_i,b_i)\leq v_j=\max(a_j,b_j) \end{cases} \iff u \text{ and } v \text{ are both sorted}}
   $$
   

## As an equivalence relation $\mathscr{C}$

- Let $a,b$ be two strings of the same length $L$

- We will define the relation $\mathscr{C}$ as follows: 
  $$
  i\mathscr{C}j \iff \exists \nu=(l,r,a,b) \text{ a co-sortable component} / \quad i,j\in[l,r]
  $$

- 

$\mathscr{C}$ is reflexive because $(i,i,a,b)$ is always a co-sortable component. Also $\mathscr{C}$ is trivially symmetric.

We will prove transitivity.

Let $i,j,k$ such that $i\mathscr{C}j$ and $j\mathscr{C}k.$ We have then:

- $\exists(l,r,a,b)$  a co-sortable component such that $i,j\in[l,r]. $ So $u_{[l\dots r]}$ and $v_{[l\dots r]}$ are sorted.
- $\exists(l',r',a,b)$  a co-sortable component such that $j,k\in[l',r'].$ So $u_{[l'\dots r']}$ and $v_{[l'\dots r']}$ are sorted.

We have $j\in [l,r]$ and $j\in [l',r'].$ Therefore, $[l,r] \cup[l',r']$ is a discrete interval $[l'',r''],$ and we have $u_{[l''\dots r'']}$ and $v_{[l''\dots r'']}$ are both sorted, which means $i\mathscr{C}k.$ 

As a conclusion, $\mathscr{C}$ is an **equivalence relation**. 

## Partition by co-Sortable components

Now $a_{[l\dots r]}$ and $b_{[l\dots r]}$ are co-sortable if and only if $l\mathscr{C}r.$ And $\mathscr{C}$ induces a partition $P_1,\dots,P_m$ of $\{1,\dots,L\}$ such that: $l,r\in P_k \iff  l\mathscr{C}r.$

Now, our original problem is reduced to for a given query $l_i\leq r_i,$ whether $l_i\mathscr{C}r_i$ or not. Now, construction of $P_1,\dots,P_m$ is trivial as they must be discrete intervals because of the following lemma:
$$
\boxed{\forall i\leq j\in\{1,\dots,L\}, \quad i\mathscr{C}j\implies \forall k\in\{i,\dots ,j\}, \quad i\mathscr{C}k}
$$
Now  $P_1,\dots,P_m$ is a partition of $\{1,\dots,L\}$ by discrete intervals. We can build it in linear time. 

Finally, for each query, we can solve the problem by finding whether $l_i,r_i$ are on a same interval $P_k$ or not using binary search.

## Complexity

$$
\mathcal{O}(n+q \log n)
$$

We can also assign to every element, the number of the corresponding interval, so that two elements are on the same co-sortable component is equivalent to finding whether the numbers of their intervals are the same or not. The complexity of this solution is:
$$
\mathcal{O}(n+q)
$$
 

