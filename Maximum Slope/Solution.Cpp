#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = INT_MIN;
    for (int i = 0; i < n-1; i++)
        ans = max(ans, a[i+1]-a[i]);
    cout << ans;
}
