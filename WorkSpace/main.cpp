// It's a wonderful life.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 

const ll N = 2000000;
ll d[N],dep[N],fa[N];

void solve(){
    int n,q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for (int i = 0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v),g[v].push_back(u);
    }

    function<void(int,int)> dfs = [&](int u,int p){
        for (auto v:g[u]){
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            if (dep[v] == 1){
                d[v] = 1;
            }else if (dep[v] > 1){
                d[v] = d[fa[u]] + int(g[u].size()) * 2;
            }
            dfs(v,u);
        }
    };
    dfs(0,0);

    while (q--){
        int u,p;
        cin >> u >> p;
        u--;
        vector<int> cnt;
        ll ans = d[u];
        while (fa[u] && u){
            cnt.push_back(g[fa[u]].size());
            u = fa[fa[u]];
        }
        sort(cnt.rbegin(),cnt.rend());
        for (int i = 0;i<min(p,(int)cnt.size());i++){
            ans -= 2 * (cnt[i] - 1);
        }
        cout << ans << endl;
    }

    return;
}

signed main(){
    // freopen("input.txt","r",stdin);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--){
        solve();
    }
    return 0;
}