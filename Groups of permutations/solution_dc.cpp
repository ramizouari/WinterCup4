#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

bool permutation_separable(const std::deque<int> &A)
{
	if (A.size() == 0)
		return true;
	int n = A.size();
	auto u = std::max_element(A.begin(), A.end());
	std::vector<int> max_pos;
	for (int i = 0; i < n; i++)
		if (A[i] == *u)
			max_pos.push_back(i);
	auto s = max_pos[max_pos.size() / 2];
	int a = std::max<int>(s - *u+1, 0),b=std::min<int>(s+*u,n);
	if (b - a < *u)
		return false;
	std::vector<int> C(*u+1);
	int distinct=0;
	for (int i = a; i < a + *u; i++)
	{
		if (C[A[i]] == 0)
			distinct++;
		C[A[i]]++;
	}
	std::deque<int> A1,A2;
	for (int k = 0; k < a; k++)
		A1.push_back(A[k]);
	for (int k = a+*u; k < n; k++)
		A2.push_back(A[k]);
	if (distinct == *u && permutation_separable(A1) && permutation_separable(A2))
		return true;
	for (int i = a+1; i <= b-*u; i++)
	{
		C[A[i - 1]]--;
		if (C[A[i - 1]] == 0)
			distinct--;
		if (C[A[i+*u-1]] == 0)
			distinct++;
		A1.push_back(A[i - 1]);
		A2.pop_front();
		C[A[i + *u - 1]]++;
		if (distinct == *u && permutation_separable(A1) && permutation_separable(A2))
			return true;
	}
	return false;
}

int main()
{
	int n;
	std::cin >> n;
	std::deque<int> A(n);
	for (auto& a : A)
		std::cin >> a;
	std::cout << (permutation_separable(A) ? "YES" : "NO") << '\n';
}