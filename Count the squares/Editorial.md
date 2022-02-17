A first observation in this problem is that the maximum possible side length of the squares we are going to find 
is min($N$,$M$). Now for a fixed side length $S$, how many squares can we find inside the rectangle?
Let's consider a Cartesian coordinate system where the origin is the bottom left point of the rectangle.
let's place the square by placing its top left inside the rectangle and consider all the possible 
coordinates of the top left point of the square. it turns out that, for a rectangle of dimensions $N$x$M$ 
and a square of side of length $S$, there are $N$-$S$+$1$ possible ordinates and $M$-$S$+$1$ possible abscissas.
Thus the total number of possible positions is ($N$-$S$+$1$)*($M$-$S$+$1$). This is the answer of a fixed side length
so the final answer is the sum over all possible values of S of ($N$-$S$+$1$)*($M$-$S$+$1$).