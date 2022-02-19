#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <filesystem>

using real = double;

auto fix_window(auto x, int L,int R)
{
	if (x < L)
		return (decltype(x))L;
	else if (x > R)
		return (decltype(x))R;
	return x;
}

int main(int argc, char**argv)
{
	std::filesystem::path path(std::filesystem::current_path());
	path += "/Test";
	std::vector<std::string> filenames;
	for (const auto& it : std::filesystem::directory_iterator(path))
		filenames.emplace_back(it.path().filename().string());
	int m = 0;
	for (const auto& f : filenames)
	{
		int r;
		if(sscanf(f.c_str(), "test%d.in",&r))
			m = std::max(m, r);
	}
	int offset=m+1;
	std::cout << "First file name: test" << offset << ".in" << "\nAre you okey with that?: ";
	bool ask_ok = false;
	std::cin >> ask_ok;
	if (!ask_ok)
		return false;
	int a,b;
	std::ifstream input("gen.cfg");
	std::random_device dev;
	std::mt19937_64 g{dev()};
	for (int i = offset; !input.eof(); i++)
	{
		int n;
		real alpha,beta;
		input >> n >> alpha >> beta;
		std::normal_distribution<real> d(alpha,beta);
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		std::vector<int> C(n), R(n);
		file << 1 << '\n' << n << '\n';
		int S1 = 0, S2 = 0;
		for (int i = 0; i < n; i++)
		{		
			C[i] = std::clamp<int>(d(g), 0, n);
			S1 += C[i];
			R[i] = std::clamp<int>(d(g), 0, n);
			S2 += R[i];
		}
		int k = n - 1;
		while (S1 < S2)
		{
			auto tmp = std::min(S2 - S1, R[k]);
			S2 -= tmp;
			R[k] -= tmp;
			k--;
		}
		k = n - 1;
		while (S2 < S1)
		{
			auto tmp = std::min(S1 - S2, C[k]);
			S1 -= tmp;
			C[k] -= tmp;
			k--;
		}
		if (S1 != S2)
			return 1;
		for (auto c : C)
			file << c << ' ';
		file << '\n';
		for (auto r : R)
			file << r << ' ';
		file.flush();
	}	
}