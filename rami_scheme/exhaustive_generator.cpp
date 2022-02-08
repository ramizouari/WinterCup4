#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
	int k = 1;
	for (int p = 2; p <= 3; p++)
	{
		for (int a = 0; a < p; a++) for (int b = 0; b < p; b++) for (int u0 = 0; u0 < p; u0++) for (int u1 = 0; u1 < p; u1++) for (int s = 1e6; s <= 1e6; s *= 100)
		{
			std::stringstream stream;
			stream << "Test/test" << k << ".in";
			std::ofstream file(stream.str());
			file << p << ' ' << a << ' ' << b << '\n' << u0 << ' ' << u1 << '\n' << s << '\n';
			for (int t = 0; t < s; t++)
				file << t << ' ';
			file.flush();
			k++;
		}
	}
}