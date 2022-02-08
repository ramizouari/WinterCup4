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
    bool alternate = true;
    while (remaining)
    {
        int l = P.size();
        for (int i = 1; i <= std::min(m,remaining); i++)
            P.push_back(i);
        if (alternate)
            std::sort(P.begin() + l, P.end(), std::less<>());
        else 
            std::sort(P.begin() + l, P.end(), std::greater<>());
        remaining -= std::min(m,remaining);
        alternate = !alternate;
    }
    std::ofstream file("test53.in");
    file << n << '\n';
    for (auto p : P)
        file << p << ' ';
    file.flush();
}