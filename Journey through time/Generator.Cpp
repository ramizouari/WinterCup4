#include <bits/stdc++.h>
#define SaveTime ios::sync_with_stdio(false), cin.tie(0);
using namespace std;
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

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

int main() {
    SaveTime
    freopen("test12.in", "w", stdout);
    int n = 200, m = 50000;
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
