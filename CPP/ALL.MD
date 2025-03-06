维护中位数，支持删除添加
、、、
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
struct maxHeap
{
    multiset<ll> pq;
    ll sum;
    maxHeap(){
        sum = 0;
    }
    void inse(ll x){
        sum += x;
        pq.insert(x);
    }
    void dele(ll x){
        sum -= x;
        auto it = pq.find(x);
        if (it != pq.end())
            pq.erase(it);
    }
    ll top(){
        if (!pq.empty())
            return *pq.rbegin();
        return -1;
    }
    ll siz(){
        return pq.size();
    }
};
struct minHeap
{
    multiset<ll> pq;
    ll sum;
    minHeap(){
        sum = 0;
    }
    void inse(ll x){
        sum += x;
        pq.insert(-x);
    }
    void dele(ll x){
        sum -= x;
        auto it = pq.find(-x);
        if (it != pq.end())
            pq.erase(it);
        else 
            cout<<"Error: The minHeap doesn't have this number!"<<endl;
    }
    ll top(){
        if (!pq.empty())
            return -*pq.rbegin();
        cout<<"Error: The minHeap is empty!"<<endl;
        return -1;
    }
    ll siz(){
        return pq.size();
    }
};

class MidiumFinder{
    private:
        maxHeap mx;
        minHeap mn;
    public:
        void inse(ll x){
            if (mx.siz()==0 || mx.top()>=x){
                mx.inse(x);
            }else{
                mn.inse(x);
            }
            if (mx.siz()>mn.siz()+1){
                mn.inse(mx.top());
                mx.dele(mx.top());
            }else if (mx.siz()<mn.siz()){
                mx.inse(mn.top());
                mn.dele(mn.top());
            }
        }
        void dele(ll x){
            if (x<=mx.top()){
                mx.dele(x);
            }else{
                mn.dele(x);
            }
            if (mx.siz()>mn.siz()+1){
                mn.inse(mx.top());
                mx.dele(mx.top());
            }else if (mx.siz()<mn.siz()){
                mx.inse(mn.top());
                mn.dele(mn.top());
            }
        }
        bool check(){
            ll cost = mx.siz() * mx.top() - mx.sum + mn.sum - mn.siz() * mx.top();
            if (cost <= k){
                return 1;
            }else{
                return 0;
            }
        }
};
、、、

找凸包
、、、cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
struct Point{
    double x,y;
    Point(double X = 0,double Y = 0){
        x = X,y = Y;
    }
    Point operator-(const Point& A){
        return Point(x-A.x,y-A.y);
    }
    double operator^(const Point& A){
        return x*A.y-A.x*y;
    }
    double dis(){
        return pow(x*x+y*y,0.5);
    }
}point[2000000];
Point q[2000000];
int tp;
bool cmp(Point A,Point B){
    Point a = A - point[1];
    Point b = B - point[1];
    if ((a^b) < 0){
        return 1;
    }else if (abs(a^b)<=0.000001){
        return a.dis() < b.dis();
    }
    return 0;
}
bool cmp1(Point A,Point B){
    if (A.y != B.y)
        return A.y < B.y;
    return A.x < B.x;
}
bool cmp2(Point A,Point B){
    if (A.x != B.x)
        return A.x < B.x;
    return A.y < B.y;
}
void solve()
{
    int n;
    //这一段把点输入到point数组就可以了
    //n表示点的数量
    sort(point+1,point+1+n,cmp1);
    sort(point+1+1,point+1+n,cmp);
    q[++tp] = point[1];
    q[++tp] = point[2];
    for (int i = 3;i<n+1;i++){
        int l = 2,r = tp,mid,ans=1;
        bool ok = 1;
        while (l<=r){
            mid = l + r >> 1;
            Point a = (q[mid] - q[mid-1]);
            Point b = point[i] - q[mid];
            if ((b^a)>=0){
                ans = mid;
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        if (!ok){
            continue;
        }
        tp = ans + 1;
        q[tp] = point[i];
    }

    double ans = 0;
    for (int i = 1;i<=tp-1;i++){
        ans +=(q[i+1]-q[i]).dis();
    }
    ans += (q[tp] - q[1]).dis();

    cout<< fixed << setprecision(2)<< ans;
    return;
}
、、、

最短路
、、、cpp
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
、、、

矩阵相关
、、、cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct Mat
{
    int n, m;
    T **a;
    Mat(int _n = 0, int _m = 0) : n(_n), m(_m)
    {
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memset(a[i], 0, sizeof(T) * m);
    }
    Mat(const Mat &B)
    {
        n = B.n, m = B.m;
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memcpy(a[i], B.a[i], sizeof(T) * m);
    }
    ~Mat() { delete[] a; }
    Mat &operator=(const Mat &B)
    {
        delete[] a;
        n = B.n, m = B.m;
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memcpy(a[i], B.a[i], sizeof(T) * m);
        return *this;
    }
    Mat operator+(const Mat &B) const
    { 
        assert(n == B.n && m == B.m);
        Mat ret(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ret.a[i][j] = (a[i][j] + B.a[i][j]) % mod;
        return ret;
    }
    Mat &operator+=(const Mat &B) { return *this = *this + B; }
    Mat operator*(const Mat &B) const
    {
        Mat ret(n, B.m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < B.m; ret.a[i][j++] %= mod)
                for (int k = 0; k < m; ++k)
                    ret.a[i][j] += a[i][k] * B.a[k][j] % mod;
        return ret;
    }
    Mat &operator*=(const Mat &B) { return *this = *this * B; }
};
Mat<int> qpow(Mat<int> A, int b)
{
    Mat<int> ret(A);
    for (--b; b; b >>= 1, A *= A)
        if (b & 1)
            ret *= A;
    return ret;
}
、、、

模板
、、、cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
void solve()
{
    return;
}
signed main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
、、、
对拍器
、、、cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    system("g++ -o gen gen.cpp");
    system("g++ -o prog1 main.cpp");
    system("g++ -o prog2 burst.cpp");

    for (int i = 0; i < 10000; ++i) 
    {
        system("gen > input.txt");               
        system("prog1 < input.txt > output1.txt"); 
        system("prog2 < input.txt > output2.txt"); 

        ifstream out1("output1.txt");
        ifstream out2("output2.txt");

        string line1, line2;
        bool same = true;
        while (getline(out1, line1) && getline(out2, line2))
        {
            if (line1 != line2)
            {
                same = false;
                break;
            }
        }
        getline(out1, line1);
        getline(out2, line2);
        if (line1 != line2)
        {
            same = false;
        }
        if (!same)
        {
            cout << "Difference found!" << endl;
            return 1;
        }
        else
        {
            cout << "Test " << i + 1 << " passed." << endl;
        }
    }
    cout << "All tests passed!" << endl;
    return 0;
}
、、、


multiset典例
、、、
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

int cnt;//这份电量/贷款的时间戳
int a[2000000];
int b[2000000];
int c[2000000];
int x[2000000];
int t[2000000];
struct daikuan
{
    int rnk,v;
    daikuan(int R = 0,int V = 0){
        rnk = R, v = V;
    }
};
struct compare {
    bool operator()(const daikuan& a, const daikuan& b) const {
        return a.rnk < b.rnk; 
    }
};
multiset<daikuan,compare> q;

int n,m;

void solve()
{
    ll sum = 0,sumDai = 0;
    cnt = 0;
    q.clear();
    cin >> n >> m;
    for (int i = 1;i<n+1;i++){
        cin >> a[i];
        b[i] = a[i],sum += a[i];
        c[i] = 0;
    }
    for (int i = 1;i<m+1;i++){
        cin >> x[i] >> t[i];
    }
    int pos = 0;
    for (int i = 1;i<m+1;i++){
        // cout<<i<<endl;
        if (sum - sumDai >= x[i] - pos){
            //处理贷款问题
            auto it = q.upper_bound(daikuan(c[t[i]],0));
            while (it != q.end() && b[t[i]]){
                if (it->v <= b[t[i]]){
                    sum -= it->v;
                    sumDai -= it->v;
                    b[t[i]] -= it->v;
                    it = q.erase(it);
                }else{
                    q.insert(daikuan(it->rnk,it->v-b[t[i]]));
                    q.erase(it);
                    sum -= b[t[i]];
                    sumDai -= b[t[i]];
                    b[t[i]] = 0;
                    break;
                }
            }
            if (x[i] - pos <= b[t[i]]){
                sum += a[t[i]] - b[t[i]];
                b[t[i]] = a[t[i]];
                c[t[i]] = ++cnt;
            }else{
                q.insert(daikuan(++cnt,x[i]-pos-b[t[i]]));
                sumDai += x[i]-pos-b[t[i]];
                sum += a[t[i]] - b[t[i]];
                b[t[i]] = a[t[i]];
                c[t[i]] = ++cnt;
            }
            pos = x[i];
        }else{
            break;
        }
        // cout <<i <<" "<<sum-sumDai<<endl;
    }
    // cout<<pos<<endl;
    pos += sum - sumDai;
    cout<<pos<<endl;
    return;
}
signed main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
、、、
