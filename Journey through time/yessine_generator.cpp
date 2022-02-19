#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
int N = 2e5, M = 199000;
std::random_device dev;
std::mt19937_64 g{ dev() };
std::uniform_int_distribution<int> d(1, 2e5);
std::uniform_int_distribution<int> h(0, 100);

int main() {
    ios_base::sync_with_stdio(false);
    freopen("testcase3.txt", "w", stdout);
    cout << N << ' ' << M << '\n';
    set<int> sp, dm;
    while (sp.size() != M) sp.insert(d(g));
    for (int i : sp) cout << i << ' ';
    cout << '\n';
    for (int i = 0; i < N; ++i) cout << h(g) << ' ';
    cout << '\n';
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        if (x > 1e5) {
            q.pop();
            continue;
        }
        q.push(2*x);
        if (x != 1e5) q.push(2*x + 1);
        cout << x << ' ' << 2*x << '\n';
        if (x != 1e5) cout << x << ' ' << 2*x + 1 << '\n';
        q.pop();
    }
}
