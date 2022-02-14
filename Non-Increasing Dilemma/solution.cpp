#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int ans = 0;
        int a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 1; i < n; i++) {
            if (a[i] > a[i-1]) {
                ans = n-i;
                break;
            }
        }
        cout << ans << '\n';
    }
}
