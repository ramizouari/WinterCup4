#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bool vis[n];
    for (int i = 0; i < n; i++)
        vis[i] = false;
    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;
        int id = -1;
        int mx = 0;
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum+= a[j];
            mx = max(mx, a[j]);
            if (mx == j-i+1 && sum == 1LL*mx*(mx+1)/2)
                id = j;
        }
        if (id != -1) {
            for (int j = i; j <= id; j++)
                vis[j] = true;
        }
        if (! vis[i])
            ans = false;
    }
    cout << (ans ? "YES" : "NO");
}
