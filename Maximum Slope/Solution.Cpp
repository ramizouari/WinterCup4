#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5+7;
int n;
int a[N];

int binarysearch() {
    int l = 0, r = 1e5+7;
    int ans = -1;
    while (l <= r) {
        int b[n];
        int m = (l+r)/2;
        for (int i = 0; i < n; i++) {
            b[i] = a[i] - (i+1)*m;
        }
        bool dec = true;
        for (int i = 0; i < n-1; i++) {
            if (b[i] < b[i+1])
                dec = false;
        }
        if (dec) {
            ans = m;
            r = m -1;
        }
        else
            l = m+1;
    }
    return ans;
}

int brute_force() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[j] >= a[i]) {
                ans = max(ans, (a[i]-a[j]+j-i-1)/(i-j));
            }
        }
    }
    return ans;
}

int main()
{
    srand(time(NULL));
    cin >>  n;
    for (int i = 0; i < n; i++) {
        a[i] = rand()%10000+1;
    }
    cout << brute_force() << ' ' << binarysearch();
}
