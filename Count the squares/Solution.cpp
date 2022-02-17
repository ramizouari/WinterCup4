//
// Created by oussamaJB on 2/16/2022.
//

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    ll n,m ;
    cin >> n >> m;
    ll s=min(n,m),ans=0;
    for(ll i=1;i<=s;++i) ans += (n-i+1)*(m-i+1);
    cout << ans << '\n';
}