#include <bits/stdc++.h>
using namespace std;

int solve(string &s, int p) {
    int n = s.size();
    reverse(s.begin(), s.end());
    long long sum[n];
    int pow_10 = 1;
    sum[0] = s[0]-'0';
    for (int i = 1; i < n; i++) {
        int d = s[i]-'0';
        pow_10 = (pow_10*10)%p;
        sum[i] = (pow_10*d+sum[i-1])%p;
    }
    long long ans = 0;
    long long dp[p];
    for (int i = 1; i < p; i++)
        dp[i] = 0;
    dp[0] = 1;
    for (int i = n-1; i >= 0; i--) {
        ans+= dp[sum[i]];
        dp[sum[i]]++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n,p; cin >> n >> p;
        string s; cin >> s;
        cout << solve(s, p) << '\n';
    }
}
