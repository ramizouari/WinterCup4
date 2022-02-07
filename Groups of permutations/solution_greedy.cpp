#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>

int main()
{
	int n;
	std::cin >> n;
	std::deque<int> A(n);
	for (auto& a : A)
		std::cin >> a;
	std::map<int, int> counter;
	int size = 0;
	for (auto a : A)
	{
		counter[a]++;
		size++;

	}
}