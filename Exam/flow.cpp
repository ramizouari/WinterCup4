#include <iostream>
#include <vector>
#include <algorithm>

bool satisfiable(std::vector<int> a, std::vector<int> b) 
{
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

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::vector<int> C1(n), C2(n);
        for (auto& c : C1)
            std::cin >> c;
        for (auto& r : C2)
            std::cin >> r;
        if (satisfiable(C1, C2))
        {
            std::vector<std::pair<int, int>> R(n);
            std::vector<std::pair<int, int>> C(n);
            for (int i = 0; i < n; i++) {
                R[i].first=C1[i];
                R[i].second = i;
            }
            for (int i = 0; i < n; i++) {
                C[i].first=C2[i];
                C[i].second = i;
            }
            std::vector<std::vector<int>>ans(n, std::vector<int>(n));
            std::sort(C.rbegin(), C.rend());
            for (int i = 0; i < n; i++) {
                std::sort(R.rbegin(), R.rend());
                for (int j = 0; j < n; j++) {
                    if (R[j].first > 0 && C[i].first > 0) {
                        ans[C[i].second][R[j].second] = 1;
                        R[j].first--;
                        C[i].first--;
                    }
                }
            }
            bool flag = true;
            for (int i = 0; i < n; ++i) flag = flag && (!C[i].first);
            for (int i = 0; i < n; ++i) flag = flag && (!R[i].first);
            if (flag) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        std::cout << ans[i][j] << ' ';
                    }
                    std::cout << '\n';
                }
            }
            else return 1;
        }
        else std::cout << -1 << '\n';
    }
}