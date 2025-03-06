#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2000000;
class Tree{
public:
    vector<int> g[N];
    int n;
    int fa[N],dep[N],siz[N];
public:
    Tree(int N) {
        n = N;
    }
    void init(){
        for (int i = 1;i<n;i++){
            int u,v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        return;
    }
    void dfs_pre(int u,int f){
        siz[u] = 1;
        fa[u] = f;
        dep[u] = dep[f] + 1;
        for (auto v:g[u]){
            if (v == f) continue;
            dfs_pre(v,u);
        }
        return;
    }
};