#include <iostream>
#include <vector>
#include <random>
#include "modular_arithmetic.h"

using IK = d_cyclic;
auto& M = IK::m, & p = M;
constexpr int N = 1e6;
constexpr integer mod = 1e9 + 7;
using IF = cyclic<mod>;
constexpr int offset = 1;
constexpr int L = 4;

int main()
{
	std::ios_base::sync_with_stdio(false);
	integer a, b, u0, u1, s;
	std::cin >> p >> a >> b >> u0 >> u1 >> s;
	std::vector<IK> u(2 * N), v(2 * N);
	u[0] = u0;
	u[1] = u1;
	v[1] = u1;
	std::vector<int> X(s);
	for (auto& x : X)
		std::cin >> x;
	for (int i = 2; i < 2 * N; i++)
	{
		u[i] = a * u[i - 1] + b * u[i - 2];
		v[i] = i * u[i] + v[i - 1];
	}
	std::random_device dev;
	std::mt19937_64 g{ dev() };
	std::uniform_int_distribution<integer> d(2, mod - 1);
	std::vector<IF> w(2 * N),H(N),H_inv(N);
	H[0] = 1;
	H_inv[0] = 1;
	IF h = d(g),h_inv=h.inv(),r=1;
	for(int i=1;i<=2*N;i++,r*=h)
		w[i] = w[i-1]+r*(integer)v[i];
	for (int i = 1; i < N; i++)
	{
		H[i] = h * H[i - 1];
		H_inv[i] = h_inv * H_inv[i - 1];
	}
	int R;
	for (R = 1; R < N; R++)
	{
		bool is_period = true;
		if ((w[2 * R] - w[R]) != w[R] * H[R])
			is_period = false;
		else for (int i = offset; i <= std::max(R,L) && is_period; i++) if (v[i] != v[i + R])
			is_period = false;
		if (is_period)
			break;
	}
	std::cout << R << '\n';
	for (auto x : X)
		std::cout << (integer)v[x] << ' ';
}