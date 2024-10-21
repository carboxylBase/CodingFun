#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class shortestPath{
    #define N 2000000
    struct Edge  
    {
        int v, w, next;
    };
    struct Node
    {
        int dis, id;
        bool operator<(const Node &a) const { return dis > a.dis; }
        Node(int d, int x) { dis = d, id = x; };
    };
    private:
        ll n;
        ll cnt = 0; 
        ll head[N];
        Edge edges[N];
        bool vis[N];
        ll dist[N];
        ll t[N];
    public:
        void add(ll u, ll v, ll w)
        {
            edges[++cnt].next = head[u];
            head[u] = cnt;
            edges[cnt].v = v;
            edges[cnt].w = w;
            return;
        }
        void dijkstra(ll pos)
        {
            priority_queue<Node> q;
            for (ll i = 1; i < n + 1; i++)
            {
                dist[i] = 0x3f3f3f3f3f3f;
            }
            memset(vis, 0, sizeof vis);
            dist[pos] = 0;
            q.push(Node(0, pos));
            while (!q.empty())
            {
                ll u = q.top().id;
                q.pop();
                if (vis[u])
                {
                    continue;
                }
                vis[u] = 1;
                for (ll i = head[u]; i; i = edges[i].next)
                {
                    ll v = edges[i].v;
                    if (dist[v] > dist[u] + edges[i].w)
                    {
                        dist[v] = dist[u] + edges[i].w;
                        if (!vis[v])
                        {
                            q.push(Node(dist[v], v));
                        }
                    }
                }
            }
            return;
        }
        //false means negative loop.
        bool spfa(int pos)
        {
            queue<int> q;
            memset(dist, 0x3f3f3f3f3f3f, sizeof dist);
            dist[pos] = 0, vis[pos] = 1;
            q.push(pos);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                vis[u] = 0;
                for (int i = head[u]; i; i = edges[i].next)
                {
                    int v = edges[i].v;
                    if (dist[v] > dist[u] + edges[i].w)
                    {
                        dist[v] = dist[u] + edges[i].w;
                        if (!vis[v])
                        {
                            vis[v] = 1;
                            q.push(v);
                            t[v]++;
                            if (t[v] == n + 1)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }
};