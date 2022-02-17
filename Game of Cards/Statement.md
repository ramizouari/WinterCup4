# Game of cards 

Rami and Yessine were learning some advanced data structures. Eventually, they got tired from writing code so they decided to take a break and play a game. 

Rami told Yessine about a game of cards he has created. In this game, each player get $N$ cards. Each card has a number written on it and the players can see each other's cards. 

They Will take turns to play. At each turn, a player must choose a prime number $P$ and the other player must find a card in his hands with a number $C$ divisible by $P$, then change the number written on that paper to $\frac{C}{P}$. The chosen prime number should be less than $L$, where $L$ is a number they agree on before the game starts. When a player is unable to find a card divisible by the prime suggested by the other players, he loses the game.  

Rami will start first. Assuming both players will play optimally, determine who will win at each game . 

***INPUT : Ths first line contains 2 integers N and L ( 1<=N<=10^4   2<=L<=10^9) The second line contains N space separated integers A[i] denoting the numbers written on Rami's cards ( 1 <= A[i] <= 10^9)  The third line contains N space separated integers B[i] denoting the numbers written on Yessine's cards ( 1 <= B[i] <= 10^9)*** 