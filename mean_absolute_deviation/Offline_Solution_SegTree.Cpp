#include <bits/stdc++.h>
#define ll long long
#define SaveTime ios_base::sync_with_stdio(false), cin.tie(0);
using namespace std;

const ll N = 1e5+7;
pair<ll,ll> tree[4*N];
ll a[N];
ll n;

pair<ll,ll> mrg(pair<ll,ll> m1, pair<ll,ll> m2) {
    pair<ll,ll> ans;
    ans.first = m1.first + m2.first;
    ans.second = m1.second + m2.second;
    return ans;
}

void upd(ll pos, pair<ll,ll> val, ll id = 0, ll ns = 0, ll ne = n-1) {
    if (pos > ne || pos < ns)
        return;
    if (ns == ne) {
        tree[id] = mrg(tree[id], val);
        return;
    }
    ll l = 2*id+1;
    ll r = 2*id+2;
    ll md = (ns+ne)/2;
    upd(pos, val, l, ns, md);
    upd(pos, val ,r, md+1, ne);
    tree[id] = mrg(tree[l], tree[r]);
}

pair<ll,ll> get(ll qs, ll qe, ll id = 0, ll ns = 0, ll ne = n-1) {
    if (ns > qe || ne < qs) {
        return {0LL,0};
    }
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    ll l = 2*id+1;
    ll r = 2*id+2;
    ll md = (ns+ne)/2;
    return mrg(get(qs, qe, l, ns, md), get(qs, qe, r, md+1, ne));
}

struct query{
    ll L,R,id;
    double av;
    query() {
        L = R = id = av = 0;
    }
    query(ll _L, ll _R, ll _id, double _av) {
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
    ll Q;
    cin >> n >> Q;
    ll cumSum[n+1]; cumSum[0] = 0;
    deque<pair<ll,ll>> val;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        val.push_back({a[i], i});
        cumSum[i+1] = cumSum[i]+a[i];
    }
    sort(val.begin(), val.end());
    vector<query> qr;
    for (ll i = 0; i < Q; i++) {
        ll L,R; cin >> L >> R; // 0 based
        L--; R--;
        qr.push_back(query(L,R,i,((1.0*cumSum[R+1]-cumSum[L])/(R-L+1))));
    }
    sort(qr.begin(), qr.end(), cmp);
    double ans[Q];
    for (auto[L,R,id,av] : qr) {
        while (!val.empty() && val[0].first-av < 1e-6) {
            upd(1LL*val[0].second, {val[0].first, 1});
            val.pop_front();
        }
        pair<ll,ll> nb = get(L,R);
        ans[id] = nb.second*av-nb.first + (av*(R-L+1) - nb.first) - (R-L+1-nb.second)*av;
        ans[id]/=(R-L+1);
    }
    for (ll i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}
