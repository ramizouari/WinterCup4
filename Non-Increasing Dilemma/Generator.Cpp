#include <bits/stdc++.h>
using namespace std;
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int mx = 1000000000;

int main() {
    freopen("test11.in", "w", stdout);
    int T = 5;
    cout << T << '\n';
    while (T--) {
        int n = 40000;
        cout << n << '\n';
        int a[n];
        for (int i = 0; i < n; i++) {
            a[i] = mt()%mx + 1;
        }
        int ans = mt()%n+1;
        sort(a, a+ans, greater<int>());
        for (int i = 0; i < n; i++)
            cout << a[i] << ' ';
        cout << '\n';
    }
}
