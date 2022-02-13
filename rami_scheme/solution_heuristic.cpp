#include <iostream>
#include <vector>
#include "modular_arithmetic.h"
#include <set>

using IK = d_cyclic;
auto& M = IK::m,&p=M;
constexpr int N = 10e6;
constexpr int offset = 1;
constexpr int L = 4;

int main()
{
	std::ios_base::sync_with_stdio(false);
	integer a, b, u0, u1, s;
	std::cin >> p >> a >> b >> u0 >> u1 >> s;
	std::vector<IK> u(2*N),v(2*N);
	u[0] = u0;
	u[1] = u1;
	v[1] = u1;
	std::vector<int> X(s);
	for (auto& x : X)
		std::cin >> x;
	for (int i = 2; i < 2*N; i++)
	{
		u[i] = a * u[i - 1] + b * u[i - 2];
		v[i] = i * u[i] + v[i - 1];
	}
	int R;
	for (R = 1; R < N; R++)
	{
		bool is_period = true;
		for (int j = offset; j <= L && is_period; j++) if (v[j] != v[j + R])
			is_period = false;		
		if (is_period)
			break;
	}
	std::cout << R << '\n';
	for (auto x : X)
		std::cout << (integer)v[x] << ' ';
}