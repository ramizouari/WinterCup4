#include <iostream>
#include <map>
#include <unordered_map>
#include "number_theory.h"
#include <algorithm>
using container = std::map<int, int>;
constexpr int L_max = 1e6;
constexpr int N = 1e6;

int main()
{
	factoriser F(L_max);
	int L;
	int n;
	std::cin >> n >> L;
	std::vector<int> A(n), B(n);
	for (auto& a : A)
		std::cin >> a;
	for (auto& b : B)
		std::cin >> b;
	container R, Y;
	for (auto a : A) for (auto [p, m] : F.prime_decomposition(a))
		if (p > L)
			break;
		else R[p] += m;
	for (auto b : B) for (auto [p, m] : F.prime_decomposition(b))
		if (p > L)
			break;
		else Y[p] += m;
	for (auto [p, _] : R) if (!Y.count(p))
		Y[p] = 0;
	for (auto [p, _] : Y) if (!R.count(p))
		R[p] = 0;
	 std::cout << (std::min_element(R.begin(), R.end(), [](const auto& P, const auto& Q)
		{
			return P.second < Q.second;
		})->second
		 >= 
	 std::min_element(Y.begin(), Y.end(), [](const auto& P, const auto& Q)
		{
			return P.second < Q.second;
		})->second ?"YES":"NO") << '\n';
}