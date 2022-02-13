#include "testlib.h"
#include <cmath>
using real = long double;
constexpr real alpha = 20;

int score(double x, double y)
{
    return std::round(200*std::exp(-alpha * std::abs(y - x)));
}

int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerTestlibCmd(argc, argv);
    // Now there are three global variables specifying testlib streams:
    // inf - stream with the testdata.
    // ouf - stream with the contestant output.
    // ans - stream with the jury answer.
    // All those streams provide the similar interface for reading data.

    // This function reads a single integer from the participant output that 
    // should be between -2000 and 2000. If it doesn't belong to the specified
    // range, checker finishes with verdict _pe and comment saying that [sum of numbers]
    // is outside of the specified range.
    real p1 = ouf.readDouble(0,1, "p");

    // This function reads a single integer from the jury output. Here we suppose
    // that jury's answer is correct and we do not need to additionally verify it.
   real p2 = ans.readDouble(); // We suppose that jury's answer is correct
   int S = score(p1, p2);
   quitp(_pc(S), "Given Score: %d", S);
}