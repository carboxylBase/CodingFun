#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2000000;
#define GRAPH_FOR(x) for (int i = graph.head[x];i;i = graph.edge[i].next)
class Graph{
public:
    struct Edge{
        int next,to,w;
    }edge[N];
    int head[N],cnt;
    Graph (int N = 0){
        for (int i = 0;i<N+1;i++){
            head[i] = 0;
        }
    }
    void init(int N){
        for (int i = 0;i<N+1;i++){
            head[i] = 0;
        }
    }
    void add(int u,int v,int w){
        edge[++cnt].next = head[u];
        head[u] = cnt;
        edge[cnt].to = v;
        edge[cnt].w = w;
    }
};
const ll M = 22;
class LcaDoubling{
public:
    Graph graph;
    int fa[N][M],n,dep[N];
    LcaDoubling(int N){
        n = N;
        for (int i = 0;i<n+1;i++){
            graph.head[i] = 0;
            dep[i] = 0;
        }
    }
    void dfs(int u){
        dep[u] = dep[fa[u][1]] + 1;
        fa[u][0] = u;
        GRAPH_FOR(u){
            int v = graph.edge[i].to;
            if (v == fa[u][1]){
                continue;
            }
            fa[v][1] = u;
            dfs(v);
        }
        return;
    }
    void init(){
        dfs(1);
        for (int i = 2;i<=M-1;i++){
            for (int j = 1;j<n+1;j++){
                fa[j][i] = fa[fa[j][i-1]][i-1];
            }
        }
    }
    int lca(int u,int v){
        if (dep[v] != dep[u]){
            if (dep[u] > dep[v]) swap(u,v);
            int tmp = dep[v] - dep[u];
            for (int i = 1;tmp;i++,tmp >>= 1){
                if (tmp & 1){
                    v = fa[v][i];
                }
            }
        }
        if (u == v){
            return u;
        }
        for (int i = M-1;i>=1;i--){
            if (fa[u][i] != fa[v][i]){
                u = fa[u][i],v = fa[v][i];
            }
        }
        return fa[u][1];
    }
};