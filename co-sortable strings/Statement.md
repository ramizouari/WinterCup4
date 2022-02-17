**Rami, Yessine** and **Oussama** frequently go together to the café to have some fun, and play card games.

After participating in a contest, they wanted to have some fun, so they decided to go to the café at $\text{16:00 pm}.$

Usually, **Oussama** is the first one to come, and he will always wait for **Rami** and **Yessine** to come $15$ to $30$ minutes late. But this time, **Rami** and **Yessine** are at the café and **Oussama** did not come yet.

As this situation is a little bit strange, **Yessine** called **Oussama** to check where he is, and of course, **Oussama** told him that he is ready, but he is just checking why his greedy solution was not accepted in the contest, and once he knows what is wrong with his solution, he will come.

Now, **Yessine** knows very well that this may take some time, so he invented a little challenge with **Rami** that will kill their time.

1. First of all, he created two strings $A$ and $B$ of the same length $L$.
2. Then, for two substring $A[l\dots r],B[l\dots r]$ of $A$ and $B$ respectively, he called them **co-sortable** if they can be simultaneously sorted using the following steps:
   - Choose $i\in\{l,\dots ,r\}$ and swap $A[i]$ and $B[i].$
   - Repeat the rule above as many times as you want.
3. Now he asked **Rami** $Q$ questions of the same type. That is , the $i^\text{th}$ question takes two parameters $l_i \leq r_i$ and is of the form:
   * **Is the subarrays $A[l_i\dots r_i]$ and $B[l_i\dots r_i]$  co-sortable?**

**Rami** was overwhelmed by the number of such questions, so he asked you to help him answer the question so that **Yessine** won't win the challenge.

