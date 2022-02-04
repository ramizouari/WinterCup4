#include <iostream>
#include <vector>
#include <cmath>

/*
* Solution correct only for K>m/2
*/

using real = long double;
using integer = long long;
constexpr int M_max = 4000;

int main()
{
	std::vector<std::vector<integer>> nCr(M_max + 1, std::vector<integer>(M_max + 1));
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
	int r = m;
	int a_max = 0;
	for (auto& a : A)
	{
		std::cin >> a;
		r -= m;
		a_max = std::max(a_max, a);
	}
	if (n == 1)
		std::cout << (m >= K) << '\n';
	else if (a_max >= K)
		std::cout << 1 << '\n';
	else if (K <= r)
	{
		real p = 0;
		for (int k = K; k <= r; k++)
			p += nCr[r][k] * std::pow((n - 1.) / n, r - 1) * std::pow(n - 1, 1 - k);
		std::cout << p << '\n';
	}
	else std::cout << 0 << '\n';

}