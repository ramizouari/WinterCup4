#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <vector>
using container = std::map<int, int>;
constexpr int L = 1e6;
constexpr int N = 1e6;


int smallest_divisor(int n)
{
	if (n < 2)
		return false;
	int l = std::ceil(std::sqrt(n));
	for (int i = 2; i <= l; i++) if (n % i == 0)
		return i;
	return n;
}

container factorise(int n)
{
	container A;
	while (n > 1)
	{
		auto p = smallest_divisor(n);
		A[p]++;
		n /= p;
	}
	return A;
}


int main()
{
	int n,L;
	std::cin >> n >> L;
	std::vector<int> A(n), B(n);
	for (auto& a : A)
		std::cin >> a;
	for (auto& b : B)
		std::cin >> b;
	container R, Y;
	for (auto a : A) for (auto [p, m] : factorise(a))
		if (p > L)
			break;
		else R[p] += m;
	for (auto b : B) for (auto [p, m] : factorise(b))
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
				})->second ? "YES" : "NO") << '\n';
}