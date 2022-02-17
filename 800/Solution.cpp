//
// Created by oussamaJB on 2/17/2022.
//

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n,m ;
    char c;
    cin >> n >> m;
    char G[n][m];
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            cin >> G[i][j];
    cin >> c;
    bool ans = true;
    if(m==1){
        for(int i=0;i<n;++i) ans = ans&&(G[i][0]==c);
    }else{
        for(int i=0;i<m;++i) ans = ans&&(G[n-1][i]==c);
    }
    if(ans)
        cout << "YES";
    else
        cout << "NO";
}