#include <bits/stdc++.h>
#define ll long long
#define SaveTime ios_base::sync_with_stdio(false), cin.tie(0);
using namespace std;
 
const int N = 1e5+7;
pair<long long,int> tree[4*N];
int a[N];
int n;
 
pair<long long,int> mrg(pair<long long,int> m1, pair<long long,int> m2) {
    pair<long long,int> ans;
    ans.first = m1.first + m2.first;
    ans.second = m1.second + m2.second;
    return ans;
}
 
void upd(int pos, pair<long long,int> val, int id = 0, int ns = 0, int ne = n-1) {
    if (pos > ne || pos < ns)
        return;
    if (ns == ne) {
        tree[id] = mrg(tree[id], val);
        return;
    }
    int l = 2*id+1;
    int r = 2*id+2;
    int md = (ns+ne)/2;
    upd(pos, val, l, ns, md);
    upd(pos, val ,r, md+1, ne);
    tree[id] = mrg(tree[l], tree[r]);
}
 
pair<long long,int> get(int qs, int qe, int id = 0, int ns = 0, int ne = n-1) {
    if (ns > qe || ne < qs) {
        return {0LL,0};
    }
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    int l = 2*id+1;
    int r = 2*id+2;
    int md = (ns+ne)/2;
    return mrg(get(qs, qe, l, ns, md), get(qs, qe, r, md+1, ne));
}
 
struct query{
    int L,R,id;
    double av;
    query() {
        L = R = id = av = 0;
    }
    query(int _L, int _R, int _id, double _av) {
        L = _L; R = _R; id = _id; av = _av;
    }
};
 
bool cmp(query q1, query q2) {
    if (q1.av < q2.av)
        return true;
    return false;
}
 
int main() {
    SaveTime
    cin >> n;
    int cumSum[n+1]; cumSum[0] = 0;
    deque<pair<int,int>> val;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        val.push_back({a[i], i});
        cumSum[i+1] = cumSum[i]+a[i];
    }
    sort(val.begin(), val.end());
    int Q; cin >> Q;
    query qr[Q];
    for (int i = 0; i < Q; i++) {
        int L,R; cin >> L >> R; // 0 based
        qr[i] = query(L,R,i,((1.0*cumSum[R+1]-cumSum[L])/(R-L+1)));
    }
    sort(qr, qr+Q, cmp);
    double ans[Q];
    for (auto[L,R,id,av] : qr) {
        while (!val.empty() && val[0].first-av < 1e-6) {
            upd(1LL*val[0].second, {val[0].first, 1});
            val.pop_front();
        }
        pair<long long,int> nb = get(L,R);
        ans[id] = nb.second*av-nb.first + (av*(R-L+1) - nb.first) - (R-L+1-nb.second)*av;
        ans[id]/=(R-L+1);
    }
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}
