#include <deque>
#include <iostream>
#include <vector>
#include <cmath>
#define SaveTime ios_base::sync_with_stdio(false), cin.tie(0);
using namespace std;

const int N = 5e6 + 7;
deque<int> v(N);
int u[N];


vector<int> z_function() {
    int n = v.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < N && v[z[i]] == v[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

#include <fstream>

int main() {
    SaveTime
        int m, a, b; cin >> m >> a >> b >> u[0] >> u[1];
    for (int i = 2; i < N; i++) {
        u[i] = (a * u[i - 1] + b * u[i - 2]) % m;
    }
    v[0] = 0;
    for (int i = 1; i < N; i++)
        v[i] = (v[i - 1] + u[i] * (i%m)) % m;
    int s; cin >> s;
    vector<int> z = z_function();
    int periode = -1;
    for (int i = 0; i < N; i++) {
        if (z[i] + i == N) {
            periode = i;
            break;
        }
    }
    if (periode == -1) {
        v.pop_front();
        z = z_function();
        for (int i = 0; i < N - 1; i++) {
            if (z[i] + i == N - 1) {
                periode = i;
                break;
            }
        }
        v.push_front(0);
    }
    cout << periode << '\n';
    for (int i = 0; i < s; i++) {
        int n; cin >> n;
        cout << v[n] << ' ';
    }
}