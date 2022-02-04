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
	auto s = std::distance(A.begin(), u);
	int a = std::max<int>(s - *u+1, 0),b=std::min<int>(s+*u,n);
	if (b - a < *u)
		return false;
	std::vector<int> C(*u+1);
	int distinct=0;
	for(int i=a;i<a+*u;i++)
		if (C[A[i]] == 0)
		{
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
	for (int i = a+1; i < b-*u; i++)
	{
		C[A[i - 1]]--;
		if (C[A[i - 1]] == 0)
			distinct--;
		if (C[A2.front()] == 0)
		{
			distinct++;
			A2.pop_front();
		}
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