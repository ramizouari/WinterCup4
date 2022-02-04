#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> R(n);
    vector<pair<int, int>> C(n);
    for (int i = 0; i < n; i++) {
        cin >> R[i].first;
        R[i].second = i;
    }
    int ans[n][n];
    for (int i = 0; i < n; i++) {
        cin >> C[i].first;
        C[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            ans[i][j] = 1;
    }
    sort(C.rbegin(), C.rend());
    for (int i = 0; i < n; i++) {
        sort(R.rbegin(), R.rend());
        for (int j = 0; j < n; j++) {
            if (R[j].first > 0 && C[i].first > 0) {
                ans[C[i].second][R[j].second] = 0;
                R[j].first--;
                C[i].first--;
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) flag = flag && (!C[i].first);
    for (int i = 0; i < n; ++i) flag = flag && (!R[i].first);
    if (flag) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << ans[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    else {
        cout << "NO\n";
    }
}
