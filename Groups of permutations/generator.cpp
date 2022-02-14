#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>


int main()
{
    std::random_device dev;
    std::mt19937_64 g(dev());
    int n;
    std::cin >> n;
    std::vector<int> P;
    int remaining = n;
    int m = std::sqrt(n);
    for (int i = 0; i < m; i++)
    {
        for (int i = m; i > 0; i--)
            P.push_back(i);
        P.push_back(3);
        P.push_back(1);
        P.push_back(2);
    }
    n = P.size();
    std::ofstream file("test56.in");
    file << n << '\n';
    for (auto p : P)
        file << p << ' ';
    file.flush();
}