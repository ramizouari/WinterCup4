#include "linear_algebra.h"
#include "modular_arithmetic.h"
#include <iostream>
#include <utility>
#include <random>
#include <fstream>
#include <chrono>

integer& M = d_cyclic::m;
using IK = d_cyclic;

using natural = std::uint64_t;
constexpr int recurrence_order = 5;


bool probable_period_check(const auto& V1, const auto& V2, const std::vector<std::pair<int, int>>& guess,
	unsigned long long offset, int limit = 1000)
{
	constexpr unsigned long long d_max = 1e15;
	static std::random_device dev;
	std::mt19937_64 g(dev());
	std::uniform_int_distribution d(0ULL, d_max);
	for (int i = 0; i < limit; i++)
	{
		auto s = d(g);
		if (V1(guess, offset + s) != V2(offset + s))
			return false;
	}
	if (V1(guess, offset) != V2(offset))
		return false;
	return true;
}

bool deterministic_period_check(const auto& V1, const auto& V2, const std::vector<std::pair<int, int>>& guess,
	unsigned long long offset)
{
	for(int i=0;i<recurrence_order;i++)
		if (V1(guess, offset+i) != V2(offset+i))
			return false;
	return true;
}


/*
* The period of V with guess
* @Requirements
* guess must be a multiple of the fundamental period
*/
void multiplicative_order(const auto& V1, const auto& V2, std::vector<std::pair<int, int>>& guess, int offset, int o = 0)
{
	for (int i = o; i < guess.size(); i++)
	{
		auto& [p, m] = guess[i];
		if (!m)
			continue;
		m--;
		if (deterministic_period_check(V1, V2, guess, offset))
		{
			multiplicative_order(V1, V2, guess, offset, i);
			return;
		}
		m++;
	}
}

natural calculate_period(const std::vector<std::pair<int, int>>& order)
{
	natural N = 1;
	for (auto [p, m] : order) for (int i = 0; i < m; i++)
		N *= p;
	return N;
}

int main(int argc, char** argv)
{
	std::ios_base::sync_with_stdio(false);
	factoriser F(1e5);
	integer a, b, s;
	std::cin >> M >> a >> b;
	IK u0, u1, u2, u3,u4,v0,v1,v2,v3,v4;
	std::cin >> (integer&)u0 >> (integer&)u1 >> s;
	u2 = a * u1 + b * u0;
	u3 = a * u2 + b * u1;
	u4 = a * u3 + b * u2;
	v0 = 0;
	v1 = u1;
	v2 = v1 + 2*u2;
	v3 = v2 + 3 * u3;
	v4 = v3 + 4 * u4;
	std::vector<integer> I(s);
	IK::assume_prime = true;
	for (auto& i : I)
		std::cin >> i;
	/*
	* prime decomposition of the multiplicative order
	* At first we calculate a guess of this order
	* The first guess is px(p²-1)x(p²-p)
	*/
	std::map<int, int> O;
	std::vector<std::pair<int, int>> order;
	for (auto [p, m] : F.prime_decomposition(M - 1))
		O[p] += 2 * m;
	for (auto [p, m] : F.prime_decomposition(M + 1))
		O[p] += m;
	O[M] += 2;
	for (auto&& [p, m] : O)
		order.emplace_back(p, m);

	IK t0=-b*b, t1=b*(b-2*a), t2=2*a*b-a*a+2*b, t3=a*a+2*a-2*b,t4=-(1+2*a);
	s_matrix<IK, 5, 5> Q({ {0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1},{-t0,-t1,-t2,-t3,-t4} });
	s_vector<IK, 5> w0({ v0,v1,v2,v3,v4 });
	auto V = [&Q,&w0](unsigned long long n)->IK
	{
		return (pow(Q, n) * w0)[0];
	};

	auto V_map = [&Q, &w0](const auto& P, unsigned long long offset = 0)->IK
	{
		auto S = Q;
		for (auto [p, m] : P)
		{
			long long alpha = 1;
			for (int i = 0; i < m; i++)
				alpha *= p;
			S = pow(S, alpha);
		}
		S *= pow(Q, offset);
		return (S*w0)[0];
	};
	multiplicative_order(V_map, V, order, 4);
	std::cout << calculate_period(order) << '\n';
	for (auto i : I)
		std::cout << (integer)V(i) << ' ';
}