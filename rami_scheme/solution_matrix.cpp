#include "linear_algebra.h"
#include "modular_arithmetic.h"
#include <iostream>
#include <utility>
#include <random>
#include <fstream>
#include <chrono>

integer &M=d_cyclic::m;
using IK = d_cyclic;


bool probable_period_check(const auto& V1, const auto& V2, const std::vector<std::pair<int,int>> &guess,
	unsigned long long offset,int limit=1000)
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

/*
* The period of V with guess
* @Requirements
* guess must be a multiple of the fundamental period
*/
void multiplicative_order(const auto &V1,const auto &V2,std::vector<std::pair<int,int>> &guess,int offset,int o=0)
{
	for (int i=o;i<guess.size();i++)
	{
		auto& [p, m] = guess[i];
		if (!m)
			continue;
		m--;
		if (probable_period_check(V1,V2,guess,offset))
		{
			multiplicative_order(V1,V2, guess,offset,i);
			return;
		}
		m++;
	}
}

integer calculate_period(const std::vector<std::pair<int,int>>& order)
{
	integer N=1;
	for (auto [p, m] : order) for (int i = 0; i < m; i++)
		N *= p;
	return N;
}

/*
* Calculates the sum: i*x^i, 0<=i<=n
* @Requirements
* s = x^(n+1)
* K = (1-x)^(-2)
* p > 2
*/
template<typename R>
R G1(R x,R n,R s,R K)
{
	static R inv_2 = R(2).inv();
	if (x == R(1))
		return n * (n + R(1))*inv_2;
	return (n * x * s - (n + R(1)) * s + x) * K;
}

int main(int argc,char **argv)
{
	std::ios_base::sync_with_stdio(false);
	factoriser F(1e5);
	integer a, b,s;
	std::cin >> M >> a >> b;
	IK u0, u1;
	std::cin >> (integer&)u0 >> (integer&)u1 >> s;
	std::vector<integer> I(s);
	IK::assume_prime = true;
	for (auto& i : I)
		std::cin >> i;
	/*
	* prime decomposition of the multiplicative order
	* At first we calculate a guess of this order
	* The first guess is p²x(p²-1)
	*/
	std::map<int, int> O;
	std::vector<std::pair<int, int>> order;
	for (auto [p, m] : F.prime_decomposition(M - 1))
		O[p] += 2*m;
	for (auto [p, m] : F.prime_decomposition(M + 1))
		O[p] += m;
	O[M]+=2;
	for (auto&& [p, m] : O)
		order.emplace_back(p, m);
	s_matrix<IK, 2, 2> A({ {0,1},{b,a} }), B = A - s_matrix<IK, 2, 2>{1};
	s_vector<IK, 2> v0({ u0,u1 });

	/*
	* Case 1: If p<=3
	* This is an edge case and need to be addresses on its own because many formulas does not work when p<=3
	* It can be proven that:
	* - 72 is always a multiple of the period
	* - The offset is always less than or equal to 2
	*/
	if (M <= 3)
	{
		constexpr int P_guess = 72;
		int offset = 2;
		int R = 1;
		std::vector<IK> U(P_guess*2+offset),V(P_guess*2+offset);
		U[0] = u0;
		U[1] = u1;
		V[0] = 0;
		V[1] = u1;
		for (int i = 2; i < 2 * P_guess+offset; i++)
		{
			U[i] = a * U[i - 1] + b * U[i - 2];
			V[i] = V[i - 1] + i * U[i];
		}

		for (int k = 1; k < P_guess; k++)
		{
			if (P_guess % k != 0)
				continue;
			int i;
			for(i=0;i<P_guess;i++)
				if (V[offset + i+k] != V[offset +i])
					break;
			if (i == P_guess)
			{
				R = k;
				break;
			}
		}
		while (offset > 0 && V[offset - 1] == V[offset + R - 1])
			offset--;
		std::cout << "Period: " << R << '\n';
		std::cout << "Offset: " << offset << '\n';
		for (auto i : I)
			std::cout << (integer)V[i < P_guess ? i : (i - offset) % R + offset] << ' ';
	}
	/*
	* Case 2: If B = A - I is an invertible matrix
	*/
	else if (B.det()!=0)
	{
		auto B2_inv = pow(B, 2).inv();
		auto V = [&A, &B, &B2_inv, &v0](unsigned long long n)->IK
		{
			auto S = pow(A, n);
			auto D = G1<s_matrix<IK, 2, 2>>(A, s_matrix<IK, 2, 2>(n), A*S, B2_inv);
			auto v = D*v0;
			return v[0];
		};

		auto V_map = [&A, &B, &B2_inv, &v0](const auto& P, unsigned long long offset = 0)->IK
		{

			auto S=A;
			IK n = 1;
			for (auto&& [p, m] : P)
			{
				long long alpha = 1;
				for (int i = 0; i < m; i++)
					alpha *= p;
				S = pow(S, alpha);
				n *= pow<IK>(p, m);
			}
			n += offset;
			S *= pow(A, offset);
			auto D = G1<s_matrix<IK,2,2>>(A,n,A*S,B2_inv);
			auto v = D*v0;
			return  v[0];
		};
		int offset = 2;
		multiplicative_order(V_map,V, order,offset);
		while (offset && V_map(order, offset-1) == V(offset-1))
			offset--;
		std::cout << "Period: " << calculate_period(order) << '\n';
		std::cout << "Offset: " << offset << '\n';
		for (auto i : I)
			std::cout << (integer)V(i) << ' ';
	}
	/*
	* Case 3: If p > 3 and B = A - I is a singular matrix
	*/
	else
	{
		IK alpha = a-2;
		/*
		* Case 3.1: If p > 3 and B = A - I is a nilpotent matrix
		*/
		if (alpha==0)
		{
			IK inv_6 = IK{ 6 }.inv(),inv_2=IK{2}.inv();
			auto V = [&A, &B, &v0, &inv_6,&inv_2 ](unsigned long long n)->IK
			{
				IK n_ = n;
				auto D = (n_ * (n_ + 1) * (2 * n_ + 1) *inv_6 )*B + n_*(n_+1)*inv_2;
				return (D * v0)[0];
			};

			auto V_map = [&A, &B, &v0, &inv_6, &inv_2](const auto& P,unsigned long long offset=0)->IK
			{

				IK n = 1;
				for (auto &&[p, m] : P)
				{
					long long alpha = 1;
					for (int i = 0; i < m; i++)
						alpha *= p;
					n *= pow<IK>(p, m);
				}
				n += offset;
				auto D = (n* (n + 1) * (2 * n + 1) * inv_6) * B + n * (n + 1) * inv_2;
				auto v = D*v0;
				return  v[0];
			};
			integer R;
			int offset = 1;
			multiplicative_order(V_map,V, order,offset);
			while (offset && V_map(order, offset-1) == V(offset-1))
				offset--;
			std::cout << "Period: " << calculate_period(order) << '\n';
			std::cout << "Offset: " << offset << '\n';
			for (auto i : I)
				std::cout << (integer)V(i) << ' ';
		}
		/*
		* Case 3.2: if p>3 and B = A - I is a diagonalisable matrix
		*/
		else
		{
			IK alpha_inv = alpha.inv(),inv_2=IK{2}.inv(),alpha_p1=alpha+1;
			auto K = pow(alpha_inv,3);
			s_vector<IK, 2> v0({ u0,u1 });
			auto V = [&A, &B, &v0, &K, &alpha_inv,&alpha_p1,&inv_2 ](unsigned long long n)->IK
			{
				auto s = pow(alpha_p1, n + 1);
				auto k = (n * alpha_p1 * s - (n + 1) * s + alpha_p1) * K;
				IK n_ = n,m=n_*(n_+1)*inv_2;
				auto D = (k-alpha_inv* m) * B + m;
				return  (D*v0)[0];
			};

			auto V_map = [&A, &B, &v0, &K, &alpha_inv, &alpha_p1, &inv_2](const auto& P,unsigned long long offset=0)->IK
			{
				auto s = alpha_p1;
				IK n = 1;
				for (auto [p, m] : P)
				{
					long long alpha = 1;
					for (int i = 0; i < m; i++)
						alpha *= p;
					s = pow(s, alpha);
					n *= pow(p, m);
				}
				n += offset;
				s *= pow(alpha_p1, offset+1);
				auto k = (n * alpha_p1 * s - (n + 1) * s + alpha_p1) * K;
				auto m = n * (n + 1) * inv_2;
				auto D = (k-alpha_inv * m) * B +  m;
				auto v = D*v0;
				return  v[0];
			};
			integer R;
			int offset = 1;
			multiplicative_order(V_map,V , order, offset);
			while (offset && V_map(order, offset-1) == V(offset-1))
				offset--;
			std::cout << "Period: " << calculate_period(order) << '\n';
			std::cout << "Offset: " << offset << '\n';
			for (auto i : I)
				std::cout << (integer)V(i) << ' ';
		}
	}
}