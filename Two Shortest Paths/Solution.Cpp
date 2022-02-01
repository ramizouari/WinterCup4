#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        // n,m < 10^4
        int n, m; cin >> n >> m;
        if (n < m)
            swap(n,m);
        int s = n + (m - 1) * 2;
        cout << s * (s + 1) / 2 + n * (n + 1) / 2 << '\n';
    }
}
