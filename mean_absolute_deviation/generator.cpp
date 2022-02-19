#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <filesystem>

using real = double;

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
	int m = 0;
	for (const auto& f : filenames)
	{
		int r;
		if (sscanf(f.c_str(), "test%d.in", &r))
			m = std::max(m, r);
	}
	int offset = m + 1;
	std::cout << "First file name: test" << offset << ".in" << "\nAre you okey with that?: ";
	bool ask_ok = false;
	std::cin >> ask_ok;
	if (!ask_ok)
		return false;
	int a, b;
	std::ifstream input("gen.cfg");
	std::random_device dev;
	std::mt19937_64 g{ dev() };
	for (int i = offset; !input.eof(); i++)
	{
		int n=1e5, m=1e5;
		std::vector<int> X(n);
		real alpha, beta;
		input >> alpha >> beta;
		std::exponential_distribution d(alpha);
		std::normal_distribution<real> h(0,beta);
		std::uniform_int_distribution U(1, n);
		int k = 0;
		for (int i=0;i<n;i++)
			X[i] = std::clamp<int>(i%2?1e9-i/2:i/2, 0, 1e9);
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		file << n << ' ' << m << '\n';
		for (auto x : X)
			file << x << ' ';
		file << '\n';
		for (int i = 0; i < m; i++)
		{
			auto mean = U(g);
			auto [a, b] = std::minmax(std::clamp<int>(mean+h(g), 1, n), std::clamp<int>(mean + h(g), 1, n));
			file << a << ' ' << b << '\n';
		}
		file.flush();
	}
}