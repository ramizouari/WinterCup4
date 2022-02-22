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

auto affine_modular_transform(auto x, auto a, auto b,auto m)
{
	return (a * x + b) % m;
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
	for (int i = offset; i <= offset && !input.eof(); i++)
	{
		constexpr int p = 44;
		int n = p*p;
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		file << n << '\n';
		std::vector<int> S(n);
		for (int i = 0; i <2*p; i++)
			S[i] = 1+i / 2;
		std::shuffle(S.begin(), S.end(),g);
		for (auto s : S) for (int i = s; i >= 1; i--)
			file << i << ' ';
		file.flush();
	}
}