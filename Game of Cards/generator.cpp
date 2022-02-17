#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include "number_theory.h"

constexpr int n = 100000;
constexpr int L = 1e6;
int main()
{
	factoriser F(L);
	int offset;
	std::random_device dev;
	std::mt19937_64 g{ dev() };
	std::ofstream file("Test/64.in");
	auto P = F.prime_list();
	file << n << ' ' << L << '\n';
	int m = P.size();
	for (int i = 0; i < n; i++)
	{
		integer r = P[i%m];
		for (int j = 0; r * P[j] < L; j++)
			r *= P[j%m];
		file << r << ' ';
	}
	file << '\n';
	for (int i = 0; i < n; i++)
	{
		integer r = P[i%m];
		for (int j = 0; r * P[j%m] < L; j++)
			r *= P[j%m];
		file << r << ' ';
	}
}