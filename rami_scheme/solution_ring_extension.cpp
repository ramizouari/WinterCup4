#include "linear_algebra.h"
#include "ring_extension.h"
#include "modular_arithmetic.h"
#include <iostream>
#include <utility>
#include <random>

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
	if (x == 1)
		return n * (n + R(1))*inv_2;
	return (n * x * s - (n + R(1)) * s + x) * K;
}

/*
* Calculates the sum: i²*x^i, 0<=i<=n
* @Requirements
* s = x^n
* C = (1-x)^(-3)
* p > 3
*/
template<typename R>
R G2(R x, R n, R s, R C)
{
	static R inv_6 = R{6}.inv();
	R K1 = n*n,
		K2 = 2 * n * n + 2 * n - 1,
		K3 = pow<R>(n+1, 2);
	if (x == 1)
		return n * (n + 1)*(2*n+1) * inv_6;
	return (-K1 *x* x * s + K2*x * s-K3*s + x+1) * C;
}

int main()
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
	IK discriminant_square = IK{ a * a } + IK{ 4 * b}, discriminant = sqrt(discriminant_square);
	/*
	* prime decomposition of the multiplicative order
	* At first we calculate a guess of this order
	* The first guess is px(p²-1)
	*/
	std::map<int, int> O;
	std::vector<std::pair<int, int>> order;
	for (auto [p, m] : F.prime_decomposition(M - 1))
		O[p] += m;
	for (auto [p, m] : F.prime_decomposition(M + 1))
		O[p] += m;
	O[M]++;
	for (auto&& [p, m] : O)
		order.emplace_back(p, m);

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
		std::cout << R << '\n';
		for (auto i : I)
			std::cout << (integer)V[i < P_guess ? i : (i - offset) % R + offset] << ' ';
	}
	/*
	* Case 2: If the characteristic polynomial is irreducible and p>3
	* Happens when: 
	* a²-4*b is a quadratic non-residue
	*/
	else if (discriminant == 0 && discriminant_square!=0 || M==2 && b%2==1 && a%2==1)
	{
		using IF = d_quadratic_extension<IK>;
		IF::a = a;
		IF::b = b;
		IF x1(0,1),x2=x1.conj(),x3(1,1e9+5);
		s_matrix<IF, 2, 2> U({ {1,1},{x1,x2} }), U_inv=U.inv(), D;
		auto Id = U * U_inv;
		s_vector<IF, 2> v0({ u0,u1 });
		auto K1 = pow(IF(1) - x1, 2).inv();
		auto V = [&U, &U_inv, &D, &v0, &x1,&K1](unsigned long long n)->IK
		{
			static std::map<unsigned long long, IF, std::greater<>> mapper;
			if (mapper.empty())
				mapper[0] = x1;
			auto [m, r] = *mapper.lower_bound(n);
			auto s1 = pow(x1, n-m)*r;
			D[0][0] = G1<IF>(x1, n, s1, K1);
			D[1][1] = D[0][0].conj();
			auto v = (U * (D * (U_inv * v0)));
			mapper[n]=s1;
			return v[0][0];
		};

		auto V_map = [&U, &U_inv, &D, &v0, &x1, &K1](const auto& P,unsigned long long offset=0)->IK
		{

			auto s1 = x1;
			IK n = 1;
			for (auto&& [p, m] : P)
			{
				long long alpha = 1;
				for (int i = 0; i < m; i++)
					alpha *= p;
				s1 = pow(s1, alpha);
				n *= pow<IK>(p, m);
			}
			n += offset;
			s1 *= pow(x1, offset);
			D[0][0] = G1<IF>(x1,n,x1*s1,K1);
			D[1][1] = D[0][0].conj();
			auto v = (U * (D * (U_inv * v0)));
			return  v[0][0];
		};
		multiplicative_order(V_map,V, order,0);
		std::cout << calculate_period(order) << '\n';
		for (auto i : I)
			std::cout << (integer)V(i) << ' ';
	}
	/*
	* Case 2: If the characteristic polynomial is reducible
	*/
	else
	{
		/*
		* Case 2.1: if p>3 and the roots are simple
		*/
		if (discriminant != 0)
		{
			IK x1 = (IK(a) - discriminant) / 2, x2 = (IK(a) + discriminant) / 2;
			s_matrix<IK, 2, 2> U({ {1,1},{x1,x2} }), U_inv = U.inv(), D;
			auto K1 = pow(IK{ 1 } - x1, 2).inv(), K2 = pow(IK{ 1 } - x2, 2).inv();
			s_vector<IK, 2> v0({ u0,u1 });
			auto V = [&U, &U_inv, &D, &v0, &x1, &x2, &K1, &K2](unsigned long long n)->IK
			{
				static std::map<unsigned long long, std::pair<IK, IK>, std::greater<>> mapper;
				if (mapper.empty())
					mapper[0] = { x1,x2 };
				auto [m, r] = *mapper.lower_bound(n);
				auto s1 = pow(x1, n - m) * r.first, s2 = pow(x2, n - m) * r.second;
				D[0][0] = G1<IK>(x1,n,s1,K1);
				D[1][1] = G1<IK>(x2, n, s2, K2);
				auto v = (U * (D * (U_inv * v0)));
				mapper[n] = { s1,s2 };
				return  v[0];
			};

			auto V_map = [&U, &U_inv, &D, &v0, &x1, &x2, &K1, &K2](const auto& P,unsigned long long offset=0)->IK
			{

				auto s1 = x1, s2 = x2;
				IK n = 1;
				for (auto &&[p, m] : P)
				{
					long long alpha = 1;
					for (int i = 0; i < m; i++)
						alpha *= p;
					s1 = pow(s1, alpha);
					s2 = pow(s2, alpha);
					n *= pow<IK>(p, m);
				}
				n += offset;
				s1 *= pow(x1, offset);
				s2 *= pow(x2, offset);
				D[0][0] = G1<IK>(x1, n, x1*s1, K1);
				D[1][1] = G1<IK>(x2, n, x2*s2, K2);
				auto v = (U * (D * (U_inv * v0)));

				return  v[0];
			};
			integer R;
			int offset = 0;
			if (x1 == 0 || x2 == 0)
				offset++;
			multiplicative_order(V_map,V, order,offset);
			while (offset && V_map(order, offset-1) == V(offset-1))
				offset--;
			std::cout << calculate_period(order) << '\n';
			for (auto i : I)
				std::cout << (integer)V(i) << ' ';
		}
		/*
		* Case 2.2: if p>3 and there is a double root
		* Todo: complete this case
		*/
		else
		{
			IK x=IK(a) / 2;
			s_matrix<IK, 2, 2> U({ {1,0},{x,1} }), U_inv = U.inv(), D;
			auto K = pow(IK{ 1 } - x, 2).inv(),C=pow(IK{1}-x,3).inv();
			s_vector<IK, 2> v0({ u0,u1 });
			auto V = [&U, &U_inv, &D, &v0, &x, &K,&C](unsigned long long n)->IK
			{
				auto s = pow(x, n);
				D[0][0] = G1<IK>(x, n, x*s, K);
				D[0][1] = G2<IK>(x, n, s, C);
				D[1][1] = D[0][0];
				auto v = (U * (D * (U_inv * v0)));
				return  v[0];
			};

			auto V_map = [&U, &U_inv, &D, &v0, &x, &K,&C](const auto& P,unsigned long long offset=0)->IK
			{
				auto s = x;
				IK n = 1;
				for (auto [p, m] : P)
				{
					long long alpha = 1;
					for (int i = 0; i < m; i++)
						alpha *= p;
					s = pow(s, alpha);
					n *= pow<IK>(p, m);
				}
				n += offset;
				s *= pow(x, offset);
	 			D[0][0] = G1<IK>(x, n, x*s, K);
				D[1][1] = D[0][0];
				D[0][1] = G2<IK>(x, n, s, C);
				auto v = (U * (D * (U_inv * v0)));
				return  v[0];
			};
			integer R;
			int offset = 0;
			if (x == 0)
				offset = 2;
			multiplicative_order(V_map,V , order, offset);
			while (offset && V_map(order, offset-1) == V(offset-1))
				offset--;
			std::cout << calculate_period(order) << '\n';
			for (auto i : I)
				std::cout << (integer)V(i) << ' ';
		}
	}
}