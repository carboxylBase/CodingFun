#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll N = 2000000;
const ll MOD = 998244353;
const ll MAX = 1e18;

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
};

class Dijkstra{
public:
	Graph* g;
	struct Node{
		int dist,idx;
		bool operator<(const Node &a) const {
			return dist > a.dist;
		}
		Node(int d,int x) {dist = d,idx = x;}
	};

	ll dist[N];
	bool vis[N];

	void dijkstra(int pos){
		priority_queue<Node> pq;
		for (int i = 1;i<g->n+1;i++){
			dist[i] = MAX;
			vis[i] = 0;
		}
		dist[pos] = 0;
		pq.push(Node(0,pos));

		while (!pq.empty()){
			int u = pq.top().idx;
			pq.pop();
			if (vis[u]){
				continue;
			}
			vis[u] = 1;
			for (int i = g->head[u];i;i = g->edge[i].next){
				int v = g->edge[i].to;
				if (dist[v] > dist[u] + g->edge[i].w){
					dist[v] = dist[u] + g->edge[i].w;
					if (!vis[v]){
						pq.push(Node(dist[v],v));
					}
				}
			}
		}
		return;
	}
};