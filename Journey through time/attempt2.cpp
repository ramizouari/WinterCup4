#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <queue>


class graph
{
	int n;
	std::vector<std::set<int>> adjacency_list;
	std::set<int> special_nodes;
	std::vector<int> cost;
	std::vector<int> parent;
public:
	graph(int _n) :n(_n), adjacency_list(n), cost(n) {}
	void connect(int a, int b)
	{
		adjacency_list[a].insert(b);
		adjacency_list[b].insert(a);
	}

	void disconnect(int a, int b)
	{
		adjacency_list[a].erase(b);
		adjacency_list[b].erase(a);
	}

	void set_cost(int k, int C)
	{
		cost[k] = C;
	}

	void set_special(int k)
	{
		special_nodes.insert(k);
	}

	int maximum_cost() const
	{
		return *std::max_element(cost.begin(), cost.end());
	}

	std::pair<int, int> best_special_node(int v) const
	{
		using triplet = std::tuple<int, std::vector<int>>;
		using couple = std::pair<std::vector<int>, int>;
		std::vector<std::vector<int>> V(n);
		std::vector<bool> visited(n);
		std::queue<triplet> Q;
		Q.push({ v,std::vector<int>(1,cost[v]) });
		V[v] = { cost[v] };
		visited[v] = true;
		while (!Q.empty())
		{
			auto [u, P] = Q.front();
			Q.pop();
			for (auto w : adjacency_list[u]) if (!visited[w])
			{
				visited[w] = true;
				V[w] = P;
				if (cost[w])
				{
					V[w].push_back(cost[w]);
					std::sort(V[w].begin(), V[w].end(), std::greater<>());
				}
				Q.push({ w,V[w] });
			}

		}
		std::vector<couple> Z;
		for (auto s : special_nodes)
			Z.emplace_back(V[s], s);
		auto it = std::max_element(Z.begin(), Z.end());
		return { it->second,it->first.front() };
	}

	bool zero_out_path(int a, int b, int p=0)
	{
		if (a == b)
		{
			cost[b] = 0;
			return true;
		}
		for (auto w : adjacency_list[a]) if (w != p)
		{
			if (zero_out_path(w, b, a))
			{
				cost[w] = 0;
				cost[a] = 0;
				return true;
			}
		}
		return false;
	}

	int minimum_cost()
	{
		int w = 0;
		int R = 0;
		while (!special_nodes.empty())
		{
			auto [s, C] = best_special_node(0);
			R += C;
			special_nodes.erase(s);
			zero_out_path(0, s);
		}
		return R;
	}
};


int main()
{
	int n, m;
	std::cin >> n >> m;
	graph G(n);
	for (int i = 0; i < m; i++)
	{
		int a;
		std::cin >> a;
		G.set_special(a - 1);
	}
	for (int i = 0; i < n; i++)
	{
		int C;
		std::cin >> C;
		G.set_cost(i, C);
	}
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		std::cin >> a >> b;
		G.connect(a - 1, b - 1);
	}
	std::cout << G.minimum_cost() << '\n';
}