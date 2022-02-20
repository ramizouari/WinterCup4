#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include "number_theory.h"
#include <filesystem>

auto fix_window(auto x, int L, int R)
{
	if (x < L)
		return (decltype(x))L;
	else if (x > R)
		return (decltype(x))R;
	return x;
}

int main(int argc, char** argv)
{
	std::filesystem::path path(std::filesystem::current_path());
	path += "/Test";
	std::vector<std::string> filenames;
	for (const auto& it : std::filesystem::directory_iterator(path))
		filenames.emplace_back(it.path().filename().string());
	int maxFileNumber = 0;
	for (const auto& f : filenames)
	{
		int r;
		if (sscanf(f.c_str(), "test%d.in", &r))
			maxFileNumber = std::max(maxFileNumber, r);
	}
	int offset = maxFileNumber + 1;
	std::cout << "First file name: test" << offset << ".in" << "\nAre you okey with that?: ";
	bool ask_ok = false;
	std::cin >> ask_ok;
	if (!ask_ok)
		return false;
	int a, b;
	std::ifstream input("gen.cfg");
	std::random_device dev;
	std::mt19937_64 g{ dev() };
	constexpr int L_max = 1e6;
	factoriser F(L_max);
	std::vector<integer> Q = F.prime_list();
	for (int i = offset; !input.eof(); i++)
	{
		int n, L;
		input >> n >> L;
		std::vector<int> P;
		std::copy(F.prime_list().begin(), std::upper_bound(F.prime_list().begin(), F.prime_list().end(), L),
			std::back_inserter(P));
		int m = P.size();
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		file << n << ' ' << 1e6 << '\n';
		for (int i = 0; i < n; i++)
		{
			int nu = std::log(L_max) / std::log(P[i % m]);
			file << (int)std::pow(P[i % m], nu - 1) << ' ';
		}
		file << '\n';
		for (int i = 0; i < n; i++)
		{
			int nu = std::log(L_max) / std::log(P[i % m]);
			file << (int)std::pow(P[i%m],nu) << ' ';
		}
		file << '\n';
		file.flush();
	}
}