#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <map>
#include <random>

template<>
struct std::hash<std::pair<int, int>>
{
	inline static std::random_device dev{};
	inline static std::mt19937_64 g{};
	inline static constexpr long long M = 1e9 + 7;
	std::uniform_int_distribution<long long> d;
	long long a, b,c;
	hash():d(1,M-1),a(d(g)),b(d(g)),c(d(g))
	{
	}
	long long operator()(const std::pair<int, int>& u) const
	{
		return (a * u.first + b * u.second + c) % M;
	}
};

bool permutation_separable(const std::deque<int> &A,int l,int r)
{
	static std::unordered_map<std::pair<int, int>,bool> mapper;
	if (mapper.count({ l,r }))
		return mapper[{l, r}];
	if (l==r)
		return true;
	int n = r-l;
	auto u = std::max_element(A.begin()+l, A.begin()+r);
	std::vector<int> max_pos;
	for (int i = l; i < r; i++)
		if (A[i] == *u)
			max_pos.push_back(i-l);
	auto s = max_pos[max_pos.size()/2];
	int a = std::max<int>(s - *u+1, 0),b=std::min<int>(s+*u,n);
	if (b - a < *u)
		return false;
	std::vector<int> C(*u+1);
	int distinct=0;
	for (int i = a; i < a + *u; i++)
	{
		if (C[A[l+i]] == 0)
			distinct++;
		C[A[l+i]]++;
	}
	if (distinct == *u && permutation_separable(A, l, std::min(l + a,r)) && permutation_separable(A, std::min(l+a+*u,r), r))
		return true;
	for (int i = a+1; i <= b-*u; i++)
	{
		C[A[l+i - 1]]--;
		if (C[A[l+i - 1]] == 0)
			distinct--;
		if (C[A[l+i+*u-1]] == 0)
			distinct++;
		C[A[l+i + *u - 1]]++;
		if (distinct == *u && permutation_separable(A, l, std::min(l + i, r)) && permutation_separable(A, std::min(l + i + *u, r), r))
		{
			mapper[{l, r}] = true;
			return true;
		}
	}
	mapper[{l, r}] = false;
	return false;
}

bool permutation_separable(const std::deque<int>& A)
{
	return permutation_separable(A, 0, A.size());
}

int main()
{
	freopen("test52.in", "r", stdin);
	int n;
	std::cin >> n;
	std::deque<int> A(n);
	for (auto& a : A)
		std::cin >> a;
	std::cout << (permutation_separable(A) ? "YES" : "NO") << '\n';
}