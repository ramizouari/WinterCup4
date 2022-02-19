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
		int R;
		input >> R;
		int k = 0;
		while (R--)
		{
			int n, m, K;
			std::uniform_int_distribution d(1, 300);
			n = d(g), m = d(g);
			real mean = static_cast<real>(m) / n;
			real alpha = std::log(m + 1);
			std::exponential_distribution<real> E(2/alpha);
			std::stringstream stream;
			stream << "Test/test" << i+k << ".in";
			std::ofstream file(stream.str());
			file << n << ' ' << m << ' ' << std::clamp<int>(mean+E(g) + 1, 2, m);
			file.flush();
			k++;
		}
	}
}