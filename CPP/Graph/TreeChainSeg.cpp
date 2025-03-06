#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2000000;

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

class SegTree{
public:
    Graph graph;    
    struct Node{
    }nodes[N*4];
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    Node merge(Node L,Node R){
        Node M;
        return M;
    }
    void build(int rt,int l,int r){
        if (l == r){
            return;
        }
        int mid = l + r >> 1;
        build(ls,l,mid),build(rs,mid+1,r);
        nodes[rt] = merge(nodes[ls],nodes[rs]);
    }
    void pd(int rt,int l,int r){
    }
    void update(int rt,int l,int r,int ql,int qr,int v){
        if (ql <= l && r <= qr){
            return;
        }
        int mid = l+r>>1;
        pd(rt,l,r);
        if (ql <= mid){
            update(ls,l,mid,ql,qr,v);
        }
        if (qr >= mid + 1){
            update(rs,mid+1,r,ql,qr,v);
        }
        nodes[rt] = merge(nodes[ls],nodes[rs]);
        return;
    }
    Node query(int rt,int l,int r,int ql,int qr){
        if (ql <= l && r <= qr){
            return nodes[rt];
        }
        int mid = l+r>>1;
        pd(rt,l,r);
        if (ql > mid){
            return query(rs,mid+1,r,ql,qr);
        }else if (qr < mid + 1){
            return query(ls,l,mid,ql,qr);
        }else{
            return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
        }
    }
};

class TreeChainSeg{
public:
    Graph graph;
    SegTree segTree;
    int fa[N],top[N],siz[N],son[N],dep[N],dfn[N],id[N],cnt,n,cnt2;
    TreeChainSeg(int N){
        graph.init(N);
        n = N;
        cnt = 0;
        cnt2 = n+1;
        for (int i = 0;i<=N;i++){
            fa[i] = top[i] = siz[i] = son[i] = dep[i] = dfn[i] = id[i] = 0;
        }
    }
    void dfs1(int u){
        siz[u] = 1;
        for (int i = graph.head[u];i;i=graph.edge[i].next){
            int v = graph.edge[i].to;
            if (fa[u] == v) continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (!son[u] || siz[son[u]] < siz[v]){
                son[u] = v;
            }
        }
    }
    void dfs2(int u,int tp){
        dfn[cnt] = u;
        id[u] = ++cnt;
        top[u] = tp;
        if (son[u]){
            dfs2(son[u],tp);
        }
        for (int i = graph.head[u];i;i=graph.edge[i].next){
            int v = graph.edge[i].to;
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v,v);
        }
    }
    void init(){
        dfs1(1),dfs2(1,1);
        segTree.graph = graph;
        segTree.build(1,1,n);
    }
    int lca(int u,int v){
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }else{
                v = fa[top[v]];
            }
        }
        if (dep[u] > dep[v]){
            return v;
        }else{
            return u;
        }
    }
};