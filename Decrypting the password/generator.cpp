#include <iostream>
#include <vector>
#include <random>
#include <fstream>


int main()
{
	std::random_device dev;
	std::mt19937_64 g(dev());
	int T,n;

	std::cin >> T >> n;
	std::uniform_int_distribution<int> d('0', '9');
	std::ofstream file("test22.in");

	file << T << '\n';
	for (int i = 0; i < T; i++)
	{
		std::string S;
		for (int i = 0; i < n; i++)
			S.push_back(d(g));
		if (S.front() == '0')
			S.front()++;
		file << n << '\n';
		file << S << std::endl;
	}
}