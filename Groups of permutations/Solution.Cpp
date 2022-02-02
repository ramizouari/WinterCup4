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
        for (int j = i; j < n; j++) {
            vector<int> v;
            for (int k = i; k <= j; k++)
                v.push_back(a[k]);
            sort(v.begin(), v.end());
            int sz = v.size();
            bool can = true;
            for (int k = 0; k < sz; k++)
                if (v[k] != k+1)
                    can = false;
            if (can)
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
