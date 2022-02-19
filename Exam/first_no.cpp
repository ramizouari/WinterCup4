#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

using real = double;

auto fix_window(auto x, int L, int R)
{
	if (x < L)
		return (decltype(x))L;
	else if (x > R)
		return (decltype(x))R;
	return x;
}

int main()
{
	int a, b;
	std::ifstream input("gen.cfg");
	int offset;
	std::cin >> offset;
	std::random_device dev;
	std::mt19937_64 g{ dev() };
	for (int i = offset; !input.eof(); i++)
	{
		int n;
		real lambda;
		input >> n >> lambda;
		std::cauchy_distribution <real> d(n / 2, lambda);
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		std::vector<int> C(n), R(n);
		file << 1 << '\n' << n << '\n';
		int S1 = 0, S2 = 0;
		for (int i = 0; i < n; i++)
		{
			C[i] = fix_window(d(g), 0, n);
			S1 += C[i];
			R[i] = fix_window(d(g), 0, n);
			S2 += R[i];
		}
		int k = n - 1;
		while (S1 < S2)
		{
			auto tmp = std::min(S2 - S1, R[k]);
			S2 -= tmp;
			R[k] -= tmp;
			k--;
		}
		k = n - 1;
		while (S2 < S1)
		{
			auto tmp = std::min(S1 - S2, C[k]);
			S1 -= tmp;
			C[k] -= tmp;
			k--;
		}
		if (S1 != S2)
			return 1;
		for (auto c : C)
			file << c << ' ';
		file << '\n';
		for (auto r : R)
			file << r << ' ';
		file.flush();
	}
}