#include <iostream>
#include <vector>
#include <cmath>
#include "modular_arithmetic.h"
#include <random>

/*
* Monte Carlo experience: used for verification
*/

using real = long double;
constexpr int M_max = 4000;
constexpr integer mod = 1e9 + 7;
using IK = cyclic<mod>;
constexpr int L=10000;
int main()
{
	int n, m, K, s;
	std::cin >> n >> m >> K >> s;
	std::vector<int> A(s);
	std::vector<std::vector<IK>>p(n+1, std::vector<IK>(m+1,0));
	for (auto& a : A)
		std::cin >> a;
	int a_max = 0, S = 0;
	for (auto a : A)
	{
		a_max = std::max(a_max, a);
		S += a;
	}
	if (a_max >= K)
	{
		std::cout << 1 << '\n';
		return false;
	}
	m -= S;
	n -= s;
	std::random_device dev;
	std::mt19937_64 g(dev());
	std::uniform_int_distribution d(0, n - 1);
	std::vector<int> B(n);
	int H = 0;
	for (int i = 0; i < L; i++) 
	{
		int B_max = 0;
		for (int i = 0; i < m; i++)
		{
			auto p = d(g);
			B[p]++;
			B_max = std::max(B_max, B[p]);
		}
		if (B_max >= K)
			H++;
		std::fill(B.begin(), B.end(), 0);
	}
	std::cout << static_cast<real>(H) / L;
}