#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

struct segment
{
	int l, r;
	bool operator<(const segment& O) const
	{
		return l < O.l;
	}

	bool operator<=(const segment& O) const
	{
		return l <= O.l;
	}

	bool operator==(const segment& O) const
	{
		return l == O.l;
	}
};

int main()
{
	int L,Q;
	std::cin >> L >> Q;
	std::string A, B;
	std::cin >> A >> B;
	for (int i = 0; i < L; i++)
	{
		auto [s1, s2] = std::minmax({ A[i], B[i] });
		A[i] = s1;
		B[i] = s2;
	}
	std::vector<segment> S;
	S.push_back({ 0,L });
	for (int i = 1; i < L; i++) if(A[i] < A[i-1] || B[i] < B[i-1])
	{
		S.back().r = i;
		S.push_back({ i,L });
	}
	for (int i = 0; i < Q; i++)
	{
		int l, r;
		std::cin >> l >> r;
		l--;
		auto [p,q] = *std::prev(std::upper_bound(S.begin(), S.end(), segment{l,r}));
		std::cout << (r <= q ? "YES" : "NO") << '\n';
	}
	return false;
}