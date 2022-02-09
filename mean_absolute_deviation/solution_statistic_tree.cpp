#include <iostream>
#include <vector>
#include <utility>
#include <variant>


/*
* * Order Statistic Tree:
* It is an AVL-tree augmented with a statistic
* The statistic is a function of:
* 1. The key
* 2. The value
* 3. left and right subtree
* @Requirements
* 1. a class T
* 2. (T,<=) is a totally ordered set
* 3. S is a statistic type
*
* * Statistic Type:
* A statistic S is a class having some attributes serving as additional informations
* Those informations can be aggregated via the static update method
* @Requirements:
* 1. class S
* 2. S has a public static method called update which accepts Tree<T,V,S>.
* 3. the update method "updates" adequately the statistics, and only the statistics
*/
template<typename T, typename V, typename S>
struct statistic_node;

template<typename T, typename V, typename S>
struct statistic_node
{
    T v;
    V data;
    int h;
    S statistic;
    statistic_node* left, * right, * parent;
    statistic_node(T _v, V _data, statistic_node* _parent = nullptr) :v(_v), data(_data), left(nullptr), right(nullptr), parent(_parent), h(1), statistic(v, data) {}
    void update()
    {
        h = std::max(left ? left->h : 0, right ? right->h : 0) + 1;
        S::update(this);
    }
};


/*
* Get the height of the (sub)-tree
*/
template<typename T, typename V, typename S>
int height(statistic_node<T, V, S>* node)
{
    return node ? node->h : 0;
}


/*
* Get the balance of the current node
*/
template<typename T, typename V, typename S>
int balance(statistic_node<T, V, S>* tree)
{
    return height(tree->left) - height(tree->right);
}

/*
* Find node that has the given key, return nullptr otherwise
* @Notes
* 1. If the value is altered, and the statistic depends on that value. The calculated statistic will not be updated.
*   In that case, better use the insert_or_assign function or the update function
* 2. If the key is altered, It will probably cause the tree to be in an inconsistent state unless the tree does not have a key
* on the interval whose limit points are the old key value, and the new one.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* find(statistic_node<T, V, S>* node, const typename std::common_type<T>::type& v)
{
    if (!node)
        return nullptr;
    if (node->v == v)
        return node->data;
    else if (node->v < v)
        return find(node->right, v);
    else return find(node->left, v);
}

/*
* Find the data mapped by the given key
* @Requirements
* The Order Statistic Tree must contain at least one such key
* @Exception
* std::logic_error thrown if no such key is found
* @Notes
* If the value is altered, and the statistic depends on that value. The calculated statistic will not be updated.
* In that case, better use the insert_or_assign function or the update function
*/
template<typename T, typename V, typename S>
V& value_at(statistic_node<T, V, S>* node, const typename std::common_type<T>::type& v)
{
    [[unlikely]]
    if (!node)
        throw std::out_of_range("key does not exist");
    if (node->v == v)
        return node;
    else if (node->v < v)
        return value_at(node->right, v);
    else return value_at(node->left, v);
}

/*
* Get the node whose key is strictly bigger than v
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* upper_bound(statistic_node<T, V, S>* tree, const
    typename std::common_type<T>::type& v)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->v <= v)
        return upper_bound(tree->right, v);
    else
    {
        auto w = upper_bound(tree->left, v);
        if (w == nullptr)
            return tree;
        return w;
    }
}

/*
* Get the node whose key is strictly smaller than v
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* reverse_upper_bound(statistic_node<T, V, S>* tree,
    const typename std::common_type<T>::type& v)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->v >= v)
        return reverse_upper_bound(tree->left, v);
    else
    {
        auto w = reverse_upper_bound(tree->right, v);
        if (w == nullptr)
            return tree;
        return w;
    }
}

/*
* Get the node whose key is not smaller than v
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* lower_bound(statistic_node<T, V, S>* tree,
    const typename std::common_type<T>::type& v)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->v < v)
        return lower_bound(tree->right, v);
    else
    {
        auto w = lower_bound(tree->left, v);
        if (w == nullptr)
            return tree;
        return w;
    }
}

template<typename T, typename V, typename S>
statistic_node<T, V, S>* reverse_lower_bound(statistic_node<T, V, S>* tree,
    const typename std::common_type<T>::type& v)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->v > v)
        return reverse_lower_bound(tree->left, v);
    else
    {
        auto w = reverse_lower_bound(tree->right, v);
        if (w == nullptr)
            return tree;
        return w;
    }
}

/*
* Get the node with the smallest key
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* begin(statistic_node<T, V, S>* tree)
{
    if (!tree)
        return nullptr;
    while (tree->left)
        tree = tree->left;
    return tree;
}

/*
* Get the successor of the current node
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* next(statistic_node<T, V, S>* tree)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->right)
    {
        tree = tree->right;
        while (tree->left)
            tree = tree->left;
        return tree;
    }
    else
    {
        auto tmp = tree;
        tree = tree->parent;
        while (tree && tree->v < tmp->v)
            tree = tree->parent;
        if (!tree)
            return nullptr;
        return tree;
    }
}

/*
* Get the previous of the current node
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* prev(statistic_node<T, V, S>* tree)
{
    if (tree == nullptr)
        return nullptr;
    if (tree->left)
    {
        tree = tree->left;
        while (tree->right)
            tree = tree->right;
        return tree;
    }
    else
    {
        auto tmp = tree;
        tree = tree->parent;
        while (tree && tree->v > tmp->v)
            tree = tree->parent;
        if (!tree)
            return nullptr;
        return tree;
    }
}

template<typename T, typename V, typename OrderStats>
int size(statistic_node<T, V, OrderStats>* node)
{
    return node ? node->statistic.size : 0;
}


/*
* Applies a right rotation to the ordered statistic tree on the current node.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* rebalance_right(statistic_node<T, V, S>* x)
{
    auto y = x->left, B = y->right;
    y->right = x;
    y->parent = x->parent;
    if (x->parent)
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else x->parent->right = y;
    }
    x->parent = y;
    x->left = B;
    if (B) B->parent = x;
    x->update();
    return y;
}

/*
* Applies a left rotation to the ordered statistic tree on the current node.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* rebalance_left(statistic_node<T, V, S>* x)
{
    auto y = x->right, B = y->left;
    y->left = x;
    y->parent = x->parent;
    if (x->parent)
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else x->parent->right = y;
    }
    x->parent = y;
    x->right = B;
    if (B) B->parent = x;
    x->update();
    return y;
}

/*
* Rebalance the ordered statistic tree.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* rebalance(statistic_node<T, V, S>* x)
{
    if (!x)
        return nullptr;
    if (balance(x) < -1)
    {
        if (balance(x->right) == 1)
            rebalance_right(x->right);
        x = rebalance_left(x);
    }
    else if (balance(x) > 1)
    {
        if (balance(x->left) == -1)
            rebalance_left(x->left);
        x = rebalance_right(x);
    }
    x->update();
    if (!x->parent)
        return x;
    return rebalance(x->parent);
}

/*
* Insert (v,data) into the ordered statistic tree
* @Cases
* 1. If or_assign is false, (v,data) is inserted while allowing duplicates
* 2. if or_assign is true, (v,data) is inserted if the tree does not have a key v. Otherwise the value mapped by v is changed to data.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* insert(statistic_node<T, V, S>* tree, const typename std::common_type<T>::type& v,
    const typename std::common_type<V>::type& data, bool or_assign = false)
{
    if (!tree)
    {
        tree = new statistic_node<T, V, S>(v, data);
        return tree;
    }
    auto p = lower_bound(tree, v);
    if (p == nullptr)
    {
        p = tree;
        while (p->right) p = p->right;
    }
    else if (or_assign && p->v == v)
    {
        p->data = data;
        p->update();
        return rebalance(p);
    }
    else if (p->left)
    {
        p = p->left;
        while (p->right)
            p = p->right;
    }
    auto u = new statistic_node<T, V, S>(v, data, p);
    if (v <= p->v)
        p->left = u;
    else p->right = u;
    p->update();
    return rebalance(p);
}

template<typename T, typename S>
statistic_node<T, std::monostate, S>* insert(statistic_node<T, std::monostate, S>* tree,
    const typename std::common_type<T>::type& v, bool or_assign = false)
{
    return insert(tree, v, {}, or_assign);
}


/*
* Insert (v,data) into the ordered statistic tree if it does not have a key v
* Otherwise, change the value mapped by v to data.
*/
template<typename T, typename V, typename S>
statistic_node<T, V, S>* insert_or_assign(statistic_node<T, V, S>* tree, const
    typename std::common_type<T>::type& v, const typename std::common_type<V>::type& data)
{
    return insert(tree, v, data, true);
}

/*
* Insert (v,data) into the ordered statistic tree if it does not have a key v
* Otherwise, Do nothing
*/
template<typename T, typename S>
statistic_node<T, std::monostate, S>* insert_or_assign(statistic_node<T, std::monostate, S>* tree, const
    typename std::common_type<T>::type& v)
{
    return insert_or_assign(tree, v, {});
}

/*
* Extract a node from an ordered statistic tree given its key
* The node is not deleted
* @Requirements
* The tree does have a node with the given key
*/
template<typename T, typename V, typename S>
std::pair<statistic_node<T, V, S>*, statistic_node<T, V, S>*> extract(statistic_node<T, V, S>* tree, const
    typename std::common_type<T>::type& v)
{
    auto p = lower_bound(tree, v);
    if (!p)
        return { nullptr,tree };
    if (!p->left)
    {
        auto w = p->parent ? p->parent : p->right;
        if (p->parent)
        {
            if (p->parent->left == p) p->parent->left = p->right;
            else p->parent->right = p->right;
        }
        if (p->right) p->right->parent = p->parent;
        p->right = nullptr;
        p->parent = nullptr;
        return { p,rebalance(w) };
    }
    else if (!p->left->right)
    {
        auto w = p->left;
        if (p->parent)
        {
            if (p->parent->left == p) p->parent->left = p->left;
            else p->parent->right = p->left;
        }
        if (p->right) p->right->parent = w;
        w->right = p->right;
        w->parent = p->parent;
        p->right = nullptr;
        p->left = nullptr;
        p->parent = nullptr;
        return { p,rebalance(w) };
    }
    else
    {
        auto u = p->left;//Position of replacement
        while (u->right)
            u = u->right;
        auto s = u->parent;//Position of path to be updated
        s->right = u->left;
        if (u->left) u->left->parent = s;
        std::swap(u->v, p->v);
        std::swap(u->data, p->data);
        u->left = nullptr;
        u->right = nullptr;
        u->parent = nullptr;
        return { u,rebalance(s) };
    }

}


template<typename T, typename V, typename S>
statistic_node<T, V, S>* erase(statistic_node<T, V, S>* tree,
    const typename std::common_type<T>::type& v)
{
    auto P = extract(tree, v);
    delete P.first;
    return P.second;
}

template<typename T, typename V, typename S>
statistic_node<T, V, S>* update(statistic_node<T, V, S>* tree,
    const typename std::common_type<T>::type& v,
    const typename std::common_type<V>::type& data)
{
    auto p = lower_bound(tree, v);
    p->data = data;
    return rebalance(p);
}

template<typename T, typename V, typename S>
void destroy(statistic_node<T, V, S>* node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}



template<typename T, typename O>
struct key_sum_stats
{
    inline static constexpr O F = O();
    int size;
    T key_sum;
    key_sum_stats() {}
    template<typename V>
    key_sum_stats(T v, V data) :size(1), key_sum(v) {}
    template<typename V>
    static void update(statistic_node<T, V, key_sum_stats>* node);
    inline static const T& key_neutral = O::neutral;
};

template<typename T, typename O>
template<typename V>
void key_sum_stats<T, O>::update(statistic_node<T, V, key_sum_stats<T, O>>* node) {
    node->statistic.size = (node->left ? node->left->statistic.size : 0) + 1 + (node->right ? node->right->statistic.size : 0);
    node->statistic.key_sum = F(tree_key_sum(node->left), node->v, tree_key_sum(node->right));
}


template<typename T, typename V, typename KeySumStats>
T tree_key_sum(statistic_node<T, V, KeySumStats>* node)
{
    return node ? node->statistic.key_sum : KeySumStats::key_neutral;
}

template<typename T, typename V, typename KeySumStats>
T prefix_key_sum(statistic_node<T, V, KeySumStats>* tree, const
    typename std::common_type<T>::type& U)
{
    if (!tree)
        return KeySumStats::key_neutral;
    else if (tree->v >= U)
        return prefix_key_sum(tree->left, U);
    else return KeySumStats::F(tree_key_sum(tree->left), tree->v, prefix_key_sum(tree->right, U));
}

template<typename T, typename V, typename KeySumStats>
T suffix_key_sum(statistic_node<T, V, KeySumStats>* tree, const
    typename std::common_type<T>::type& L)
{
    if (!tree)
        return KeySumStats::key_neutral;
    else if (tree->v < L)
        return suffix_key_sum(tree->right, L);
    else return KeySumStats::F(suffix_key_sum(tree->left, L), tree->v, tree_key_sum(tree->right));
}

template<typename T, typename V, typename KeySumStats>
T key_sum(statistic_node<T, V, KeySumStats>* tree, const typename std::common_type<T>::type& L,
    const typename std::common_type<T>::type& R)
{
    if (!tree)
        return KeySumStats::key_neutral;
    if (tree->v < L)
        return key_sum(tree->right, L, R);
    else if (tree->v >= R)
        return key_sum(tree->left, L, R);
    else return KeySumStats::F(suffix_key_sum(tree->left, L), tree->v, prefix_key_sum(tree->right, R));
}

template<typename T, typename V, typename KeySumStats>
T prefix_index_key_sum(statistic_node<T, V, KeySumStats>* tree, int n)
{
    if (!tree || n <= 0)
        return KeySumStats::key_neutral;
    else if (size(tree->left) >= n)
        return prefix_index_key_sum(tree->left, n);
    else return KeySumStats::F(tree_key_sum(tree->left), tree->v, prefix_index_key_sum(tree->right, n - 1 - size(tree->left)));
}

template<typename T, typename V, typename KeySumStats>
T suffix_index_key_sum(statistic_node<T, V, KeySumStats>* tree, int n)
{
    if (!tree)
        return KeySumStats::key_neutral;
    else if (size(tree->right) >= n)
        return suffix_index_key_sum(tree->right, n);
    else return KeySumStats::F(suffix_index_key_sum(tree->left, n - 1 - size(tree->right)), tree->v, tree_key_sum(tree->right));
}

template<typename T, typename V, typename KeySumStats>
T index_key_sum(statistic_node<T, V, KeySumStats>* tree, int a, int b)
{
    if (!tree || a >= b)
        return KeySumStats::key_neutral;
    int left_size = size(tree->left);
    if (left_size < a)
        return KeySumStats::F(tree->v, index_key_sum(tree->right, a - left_size - 1, b - left_size - 1));
    else if (left_size >= b)
        return index_key_sum(tree->left, a, b);
    else return KeySumStats::F(suffix_index_key_sum(tree->left, left_size - a), tree->v, prefix_index_key_sum(tree->right, b - left_size - 1));
}


template<typename T, typename O, typename V = std::monostate>
using key_sum_node = statistic_node<T, V, key_sum_stats<T, O>>;
template<typename T, template<typename S = T> typename O, typename V = std::monostate>
using key_sum_node_t = statistic_node<T, V, key_sum_stats<T, O<T>>>;


template<typename T>
struct binary_operation
{
	template<typename H0, typename ...H>
	T operator()(const H0& a, const H&... b) const
	{
		if constexpr (sizeof...(b) == 0)
			return a;
		else return reduce(a, this->operator()(b...));
	}
	virtual T reduce(const T& a, const T& b) const = 0;
};

template<typename T>
struct plus_t :public binary_operation<T>
{
	T reduce(const T& a, const T& b) const override
	{
		return a + b;
	}

	T inv(const T& a) const
	{
		return -a;
	}
	inline static T neutral = T();
};

struct result_t
{
	double S1;
	double S2;
	int o;

	result_t& operator+=(const result_t& O)
	{
		S1 += O.S1;
		S2 += O.S2;
		o += O.o; 
		return *this;
	}

	result_t operator+(const result_t& O) const
	{
		return { S1 + O.S1,S2 + O.S2,o + O.o };
	}
};

struct sum_t
{
	double sum = 0;
	int n = 0;
	sum_t& operator+=(const sum_t& O)
	{
		sum += O.sum;
		n += O.n;
		return *this;
	}

	sum_t operator+(const sum_t& O) const
	{
		return { sum + O.sum,n + O.n };
	}
};

result_t result(key_sum_node_t<double, plus_t>* node, double mean)
{
	if (!node)
		return { 0,0,0 };
	result_t R;
	if (node->v < mean)
	{
		R = result(node->right, mean);
		R.S1 += tree_key_sum(node->left) + node->v;
		R.o += size(node->left) + 1;
	}
	else
	{
		R = result(node->left, mean);
		R.S2 += tree_key_sum(node->right) + node->v;
	}
	return R;
}

unsigned int bit_log(unsigned int n)
{
    unsigned char a = 0, b = 30, r = 0;
    while (a <= b)
    {
        auto c = (a + b) / 2;
        if (n >> c)
            a = c + 1;
        else
        {
            b = c - 1;
            r = c - 1;
        }
    }
    if ((1 << (r - 1)) == n)
        return r - 1;
    return r;
}

unsigned int bit_floor(unsigned int n)
{
    return 1 << bit_log(n);
}

unsigned int bit_ceil(unsigned int n)
{
    return 1 << (bit_log(n) + 1);
}


struct aggregate_tree
{
	using R = key_sum_node_t<double, plus_t>*;
	std::vector<std::vector<R>> S;
	std::vector<double> A;
	int n, h;
	aggregate_tree(const std::vector<double>& _A) :A(_A)
	{
		n = bit_ceil(A.size());
		A.resize(n, 0);
		int m = n;
		h = 0;
		while (m)
		{
			m /= 2;
			h++;
		}
		S.resize(h);
		for (int i = 0; i < h; i++)
			S[i].resize(1 << i, nullptr);
		build();
	}
	~aggregate_tree()
	{
		for (auto& R : S) for (auto p : R)
			destroy(p);
	}

	void update(int i, double u)
	{
		double tmp = A[i];
		A[i] = u;
		int m = h - 1;
		while (m >= 0)
		{
			S[m][i] = erase(S[m][i], tmp);
			S[m][i] = insert(S[m][i], A[i]);
			m--;
			i /= 2;
		}
	}

	result_t query(int l, int r)
	{
		auto [s, _] = sum(std::max(l, 0), std::min(r, n), 0, n, 0);
		auto m = std::min(r, n) - std::max(l, 0);
		return query(std::max(l, 0), std::min(r, n), 0, n, 0, s / m);
	}
private:
	inline static constexpr plus_t<double> F{};
	void build()
	{
		for (int i = h - 1; i >= 0; i--) for (int k = 0; k < (1 << i); k++) for (int r = 0; r < (1 << (h - 1 - i)); r++)
			S[i][k] = insert(S[i][k], A[(1 << (h - 1 - i)) * k + r]);
	}
	result_t query(int l, int r, int a, int b, int depth, double mean)
	{
		if (l >= r)
			return { 0,0,0 };
		if (l == a && r == b)
			return result(S[depth][l >> (h - 1 - depth)], mean);
		int mid = (a + b) / 2;
		if (mid > r)
			return query(l, r, a, mid, depth + 1, mean);
		else if (mid < l)
			return query(l, r, mid, b, depth + 1, mean);
		else
			return query(l, mid, a, mid, depth + 1, mean) + query(mid, r, mid, b, depth + 1, mean);
	}

	sum_t sum(int l, int r, int a, int b, int depth)
	{
		if (l >= r)
			return { 0,0 };
		if (l == a && r == b)
			return { tree_key_sum(S[depth][l >> (h - 1 - depth)]),size(S[depth][l >> (h - 1 - depth)]) };
		int mid = (a + b) / 2;
		if (mid > r)
			return sum(l, r, a, mid, depth + 1);
		else if (mid < l)
			return sum(l, r, mid, b, depth + 1);
		else
			return sum(l, mid, a, mid, depth + 1) + sum(mid, r, mid, b, depth + 1);
	}
};


#include <random>
int main()
{
	std::ios_base::sync_with_stdio(false);
	int n, q;
	std::cin >> n >> q;
	std::vector<double> X(n);
	std::vector<std::pair<int, int>> S(q);
	std::vector<double> R;
	std::random_device dev;
	std::mt19937_64 g(dev());
	std::exponential_distribution<double> d_double(.1);
	std::uniform_int_distribution d(0, n - 1);
    for (auto& x : X)
    {
        //x = d_double(g);
        std::cin >> x;
    }
	aggregate_tree T(X);
	for (auto& [l, r] : S)
	{
		/*int u = d(g), v = d(g);
		auto [p, q] = std::minmax(u, v);
		l = p;
		r = q + 1;
        */
		std::cin >> l >> r;
        l--;
		auto [S1, S2, o] = T.query(l, r);
		int m = r - l;
		double a = 2. * o / m, b = 2. * (m - o) / m;
		R.push_back((a * S2 - b * S1) / m);
	}
	for (auto r : R)
		std::cout << r << '\t';
}