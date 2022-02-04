#include <bits/stdc++.h>
#define ll long long
using namespace std;

bool satisfiable(std::vector<int> a, std::vector<int> b) {
    while (!a.empty()) {
        std::sort(b.begin(), b.end(), std::greater<int>());
        int k = a.back();
        a.pop_back();
        if (k > b.size()) return false;
        if (k == 0) continue;
        if (b[k - 1] == 0) return false;
        for (int i = 0; i < k; i++)
            b[i]--;
    }
    for (std::vector<int>::iterator i = b.begin(); i != b.end(); i++)
        if (*i != 0)
            return false;
    return true;
}

bool brute_force(vector<int> C, vector<int> R) {
    int n = C.size();
    sort(C.rbegin(), C.rend());
    for (int i = 0; i < n; ++i) {
        sort(R.rbegin(), R.rend());
        for (int j = 0; j < n; ++j) {
            if (C[i] && R[j]) {
                R[j]--;
                C[i]--;
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) flag = flag && (!C[i]);
    for (int i = 0; i < n; ++i) flag = flag && (!R[i]);
    return flag;
}

int n;
vector<int> row;
vector<int> column;

void exhaustive_search(int id1 = 0, int id2 = 0) {
    if (id1 == n && id2 == n) {
        if (brute_force(row, column) != satisfiable(row, column)) {
            cout << "! contre exemple ! \n";
            for (int i : row)
                cout << i << ' ';
            cout << '\n';
            for (int i : column)
                cout << i << ' ';
            cout << '\n';
        }
        return;
    }
    if (id1 == n) {
        for (int i = 0; i <= n; i++) {
            column.push_back(i);
            exhaustive_search(id1, id2+1);
            column.pop_back();
        }
        return;
    }
    for (int i = 0; i <= n; i++) {
        row.push_back(i);
        exhaustive_search(id1+1, id2);
        row.pop_back();
    }
}

// Driver Code
int main()
{
    cin >> n;
    exhaustive_search();
}
