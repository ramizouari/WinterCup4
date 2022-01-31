#include <bits/stdc++.h>
using namespace std;

int solve(string &s) {
    int n = s.size();
    int cumSum = 0;
    long long ans = 0;
    long long dp[11];
    for (int i = 1; i < 11; i++)
        dp[i] = 0;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int digit = s[i]-'0';
        if (i%2) {
            cumSum = (cumSum+digit)%11;
        }
        else {
            cumSum = (cumSum-digit+11)%11;
        }
        ans+= dp[cumSum];
        dp[cumSum]++;
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        string s; cin >> s;
        cout << solve(s) << '\n';
    } 
}
