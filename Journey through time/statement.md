Oussama is a student. Next year will be his last one at university so he will need to find a graduation internship.
He wants to find an internship abroad but he is afraid he won't be able to travel due to the wide spread of COVID19,
so he started thinking about a way to end the pandemic. Suddenly, a very good idea hit him : he will make a time machine
and go back in time to find the very first infected persons and save them from the infection thus preventing the pandemic.
However, time travel is dangerous and can cause some serious damage.

You might have heard that the timeline is linear, but it is not. In fact, the timeline is a tree of $N$ nodes,
where each node is a different time. Each node $i$ causes a certain damage $$D_i$$.
There are $M$ special nodes. Each special node denotes a time of an infection that should be stopped.
Oussama is initially at the present, which is node 1, and will visit each one of the special nodes in any order he wants.
Whenever he moves from a node $A$ to a node $B$, he will get a damage equal to the maximum node damage on the path between $A$ and $B$.
However, he won't get any more damage from the nodes on that path after the first time he travels through it.
In other words, after he walks through a path and takes the damage, the damage of the nodes on that path become zeros.
When he visits the node he wants, he stops to prevent the infection from happening and then travel from there to one of the remaining special nodes.
He repeats the same process until every special node is visited . The total damage he will get is the sum of the damages obtained on each move.

Oussama wants to save the world  from the pandemic but he has a limited stamina so he can't take too much damage.
Help him determine the minimal damage he will take during the time travel .

INPUT:
The first line contains 2 integers $N$ and $M$ (1<=$M<$=$N$<=10^5)
The second line contains M space separated integers denoting the indices of special nodes.
The third line contains N space separated integers denoting the damage of each node.
Finally, there are $N$-1 lines, each line contains 2 space separated integers U V which indicates that there is an edge between nodes U and V.
