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
	constexpr int N = 446*446;
	for (int i = offset; !input.eof(); i++)
	{
		int C, R;
		input >> C >> R;
		std::stringstream stream;
		stream << "Test/test" << i  << ".in";
		std::ofstream file(stream.str());
		std::vector<std::pair<int, int>> E;
		std::uniform_int_distribution d(0, C);
		int K = std::sqrt(N);
		int size = 1;
		for (int i = 1; i < K; i++)
		{
			size++;
			E.emplace_back(0, i);
		}
		for (int i = 0; i < K; i++)
		{
			size++;
			E.emplace_back(i + 1, (i + 1) * K);
			for (int j = 0; j < K-1; j++)
			{
				size++;
				E.emplace_back((i + 1) * K  + j, (i + 1) * K + 1 + j);
			}
		}
		std::vector<int> V(size), S(R);
		for (int i = 0; i < size; i++)
			V[i] = i;
		std::shuffle(V.begin(), V.end(), g);
		std::copy(V.begin(), V.begin() + R, S.begin());
		file << size << ' ' << R << '\n';
		for (auto s : S)
			file << s+1 << ' ';
		file << '\n';
		for (int i = 0; i < size; i++)
			file << d(g) << ' ';
		file << '\n';
		for (auto [a, b] : E)
			file << a+1 << ' ' << b+1 << '\n';
		file.flush();	
	}
}