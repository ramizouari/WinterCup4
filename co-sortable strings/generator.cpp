#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
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
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for (int i = offset; !input.eof(); i++)
	{
		int n, Q,K;
		double alpha;
		input >> n >> Q >> alpha >> K;
		std::vector<int> P;
		std::stringstream stream;
		stream << "Test/test" << i << ".in";
		std::ofstream file(stream.str());
		file << n << ' ' << Q << '\n';
		std::uniform_int_distribution d(1, n);
		std::uniform_int_distribution<int> h(0, alphabet.length()-1);
		std::normal_distribution<double> N(0, alpha);
		std::string A, B;
		int size = alphabet.size();
		using namespace std::string_literals;
		for (int i = 0; i < n; i++)
		{
			A.push_back(alphabet[(size-1-i%size) % size]);
			B.push_back(alphabet[(size-1-i%size) % size]);
		}
		file << A << '\n' << B << '\n';
		for (int i=0;i<Q;i++)
		{
			auto mean = d(g);
			auto [p, q] = std::minmax(std::clamp<int>(mean+N(g),1,n), std::clamp<int>(mean+N(g),1,n));
			file << p << ' ' << q << '\n';
		}
		file.flush();
	}
}