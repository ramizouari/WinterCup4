#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
//#include <boost/multiprecision/cpp_bin_float.hpp>

//using real = boost::multiprecision::number<boost::multiprecision::cpp_bin_float<1000> >;
using real = double;
constexpr int M_max = 300;
constexpr real eps = 1e-9;

int main()
{
	std::vector<std::vector<real>> nCr(M_max + 1, std::vector<real>(M_max + 1));
	nCr[0][0] = 1;
	for (int i = 1; i <= M_max; i++) for(int j = 0; j <= i; j++)
	{
		nCr[i][j] = nCr[i - 1][j];
		if (j > 0)
			nCr[i][j] += nCr[i - 1][j - 1];
	}
	int n, m, K, s=0;
	std::cin >> n >> m >> K;
	std::vector<int> A(s);
	std::vector<std::vector<real>>p(n+1, std::vector<real>(m+1,0.L));
	for (auto& a : A)
		std::cin >> a;
	int a_max=0,S=0;
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
	for (int j = K; j <= m; j++)
		p[1][j] = 1;
	for (int i = 2; i <= n; i++)
	{
		real h = (i - 1.L) / i;
		real w = std::pow(h,K);
		for (int j = K; j <= m; j++)
		{
			p[i][j] = 1;
			real a = i-1,b=1;
			for (int k = 0; k <= K - 1; k++)
			{
				p[i][j] -= nCr[j][k] *b * w * (1 - p[i - 1][j - k]);
				b /= a;
			}
			w *= h;
		}
	}
	std::cout << std::max<real>(p[n][m],0) << '\n';
}