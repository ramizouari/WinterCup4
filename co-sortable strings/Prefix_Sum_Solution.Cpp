#include <bits/stdc++.h>
using namespace std;

int main() {
    int l,q; cin >> l >> q;
    string a,b; cin >> a >> b;
    for (int i = 0; i < l; i++) {
        if (a[i] > b[i])
            swap(a[i], b[i]);
    }
    int cumA[l];
    int cumB[l];
    cumA[0] = cumB[0] = 0;
    for (int i = 1; i < l; i++) {
        cumA[i] = cumA[i-1] + (a[i-1] > a[i]);
        cumB[i] = cumB[i-1] + (b[i-1] > b[i]);
    }
    for (int i = 0; i < q; i++) {
        int l,r; cin >> l >> r;
        l--; r--;
        int nbA = cumA[r]-cumA[l+1];
        int nbB = cumB[r]-cumB[l+1];
        cout << ((nbA+nbB == 0) ? "YES\n" : "NO\n" );
    }
}
