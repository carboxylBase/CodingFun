#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2000000;
#define GRAPH_FOR(x) for (int i = graph.head[x];i;i = graph.edge[i].next)
class Graph{
public:
    int n;// 点的总数
    struct Edge{
        int next,to,w;
    }edge[N];
    int head[N],cnt;
    void add(int u,int v,int w){
        edge[++cnt].next = head[u];
        head[u] = cnt;
        edge[cnt].to = v;
        edge[cnt].w = w;
    }
	void init(int N){
		n = N;
		for (int i = 1;i<n+1;i++){
			head[i] = 0;
		}
		cnt = 0;
		return;
	}
}g;