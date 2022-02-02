#include <iostream>
#include <vector>
#include <cmath>
#include "modular_arithmetic.h"

using real = long double;
constexpr int M_max = 4000;
constexpr integer mod = 1e9 + 7;
using IK = cyclic<mod>;

int main()
{
	std::vector<std::vector<IK>> nCr(M_max + 1, std::vector<IK>(M_max + 1));
	nCr[0][0] = 1;
	for (int i = 1; i <= M_max; i++) for(int j = 0; j <= i; j++)
	{
		nCr[i][j] = nCr[i - 1][j];
		if (j > 0)
			nCr[i][j] += nCr[i - 1][j - 1];
	}
	int n, m, K, s;
	std::cin >> n >> m >> K >> s;
	std::vector<int> A(s);
	std::vector<std::vector<IK>>p(n+1, std::vector<IK>(m+1,0));
	for (auto& a : A)
		std::cin >> a;
	for (int j = K; j <= m; j++)
		p[1][j] = 1;
	for (int i = 2; i <= n; i++)
	{
		IK h = IK{ i - 1 } / i;
		for (int j = K; j <= m; j++)
		{
			p[i][j] = 1;
			for (int k = 0; k <= K - 1; k++)
				p[i][j] -= nCr[j][k] * pow<IK>(i - 1, k).inv() * pow(h, j) * (IK{ 1 } - p[i - 1][j - k]);
		}
	}
	std::cout << (integer)p[n][m] << '\n';
}