#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#define SaveTime ios::sync_with_stdio(false), cin.tie(0);
using namespace std;
std::random_device dev;
mt19937_64 mt(dev());

const int mx = 2e5+7;

int par[mx];

int Find(int node) {
    if (par[node] == node)
        return node;
    return par[node] = Find(par[node]);
}

bool Union(int n1, int n2) {
    int a1 = Find(n1);
    int a2 = Find(n2);
    if (a1 == a2)
        return false;
    par[a1] = a2;
    return true;
}

int main(int argc, char **argv) {
    SaveTime
    int n = 2000, m = 1200;
    if (argc > 1)
    {
        std::stringstream stream;
        n = std::stoi(argv[1]);
        m = std::stoi(argv[2]);
        if (argc == 4)
        {
            unsigned long long seed = std::stoull(argv[3]);
            mt.seed(seed);
        }
    }
    cout << n << ' ' << m << '\n';
    vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(i+1);
    }
    for (int i = 0; i < mx; i++)
        par[i] = i;
    shuffle(v.begin(), v.end(), mt);
    vector<int> special;
    for (int i = 0; i < m; i++)
        special.push_back(v[i]);
    sort(special.begin(), special.end());
    for (int i : special)
        cout << i << ' ';
    cout << '\n';
    for (int i = 0; i < n; i++) {
        int damage = mt()%(2*n);
        cout << damage << ' ';
    }
    cout << '\n';
    int nbEdge = 0;
    while (nbEdge != n-1) {
        int a = mt()%n+1;
        int b = mt()%n+1;
        if (a == b)
            continue;
        if (Union(a,b)) {
            cout << a << ' ' << b << '\n';
            nbEdge++;
        }
    }
}
