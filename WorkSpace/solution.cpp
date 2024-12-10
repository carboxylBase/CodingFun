#include <bits/stdc++.h>
 
using namespace std;
 
void solve() {
    int n, q;
    cin >> n >> q;
    
    vector < vector <int> > g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector <int> depth(n);
    vector <int> d(n);
    vector <int> par(n);
 
    function <void(int, int)> dfs = [&](int v, int p) {
        if (depth[v] == 1) d[v] = 1;
        if (depth[v] > 1) d[v] = d[par[p]] + 2 * (int)g[p].size();
        par[v] = p;
        for(int to : g[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    };
    
    dfs(0, 0);
    
    while (q--) {
        int v, p;
        cin >> v >> p;
        v--;
        int res = d[v];
        vector <int> cnt;
        while (v != 0 && par[v] != 0) {
            cnt.push_back((int)g[par[v]].size());
            v = par[par[v]];
        }
        sort(cnt.rbegin(), cnt.rend());
        for (int i = 0; i < min(p, (int)cnt.size()); i++) {
            res -= 2 * (cnt[i] - 1);
        }
        cout << res << '\n';
    }
}
 
int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
 
    return 0;
}