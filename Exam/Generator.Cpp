#include <bits/stdc++.h>
#define ll long long
using namespace std;

mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2007;
int grid[N][N];

int main() {
    freopen("random13.in", "w", stdout);
    cout << 1 << endl;
    int n = 2000;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = mt()%2;
            if (grid[i][j] == 0) {
                grid[i][j] = 0;
            }
            else
                grid[i][j] = 1;
        }
    }
    vector<int> C(n);
    vector<int> R(n);
    for (int i = 0; i < n; i++) {
        int nb1 = 0;
        int nb2 = 0;
        for (int j = 0; j < n; j++) {
            nb1+= grid[j][i];
            nb2+= grid[i][j];
        }
        C[i] = nb1;
        R[i] = nb2;
    }
    for (int i : C)
        cout << i << ' ';
    cout << endl;
    for (int i : R)
        cout << i << ' ';
}
