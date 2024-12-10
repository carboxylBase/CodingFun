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