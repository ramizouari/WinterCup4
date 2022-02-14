//
// Created by oussamaJB on 2/13/2022.
//
#include <iostream>
#include <vector>
#include <queue>
#define ll long long
using namespace std;
int n,m,x,y;
bool s[200005]={}; // special nodes
bool g[200005]={}; // good nodes
int mx[200005]={}; // max good value in the subtree
int cost[200005]={};
int v[200005]={}; // visited nodes
vector<int> adj[200005];
priority_queue<pair<int,int>> pq;

void mark_good(int node, int prev){
    if(s[node]) g[node]=true;
    for(int u : adj[node] ){
        if(u!=prev){
            mark_good(u,node);
            g[node] = g[node] || g[u];
        }
    }
}

void precompute(int node, int prev){
    int c = cost[node];
    if(g[node]){
        for(int u : adj[node] ){
            if(u!=prev){
                precompute(u,node);
                c=max(c,mx[u]);
            }
        }
    }else c=0;
    mx[node]=c;
}

void dfs(int node, int cur_max){
    //cout << "visiting " << node << " ";
    v[node]=true;
    priority_queue<pair<int,int>> ch;
    if(g[node]){
        for(int u:adj[node]){
            if(!v[u]){
                ch.push({mx[u], u});
            }
        }
        if(!ch.empty()) {
            dfs(ch.top().second, cur_max);
            ch.pop();
        }
        while(!ch.empty()){
            pq.push(ch.top());
            ch.pop();
        }
    }
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;++i){
        cin >> x;
        s[x]=true;
    }
    for(int i=1;i<=n;++i) cin >> cost[i];
    for(int i=1;i<n;++i){
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    mark_good(1,-1);
    precompute(1,-1);
    pq.push({mx[1],1});
    ll ans=0;
    while (!pq.empty())
    {
        pair<int,int> pi = pq.top();
        pq.pop();
        ans += pi.first;
        dfs(pi.second,pi.first);
        //cout << ans << '\n';
    }
    cout << ans << '\n';
}