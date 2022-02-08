#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>

constexpr long long N = 1e18;

int main()
{
	int p, a, b, u0, u1;
	std::cin >> p >> a >> b >> u0 >> u1;
	int s;
	std::cin >> s;
	std::random_device dev;
	std::mt19937_64 g(dev());
	std::uniform_int_distribution d(0LL, N);
	std::ofstream file("normal36.in");
	file << p << ' ' << a << ' ' << b << '\n';
	file << u0 << ' ' << u1 << '\n';
	file << s << '\n';
	long long L = 1e17;
	for (int i = 0; i < s; i++)
		file << L+i << ' ';
}