[TOC]

# ACM 葵花宝典

## 更新日志

+ 2025.3.1: 为了应付校赛,初版问世.

## 需要改进的地方
+ 最短路部分缺乏 Johnson .
+ 网络流模板

## 数据结构

### 线段树

常规模板:
```cpp
class SegTree{
public:
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
    void pd(int rt){

    }
    void update(int rt,int l,int r,int ql,int qr){
        if (ql <= l && r <= qr){
            return;
        }
        int mid = l+r>>1;
        pd(rt);
        if (ql <= mid){
            update(ls,l,mid,ql,qr);
        }
        if (qr >= mid + 1){
            update(rs,mid+1,r,ql,qr);
        }
        nodes[rt] = merge(nodes[ls],nodes[rs]);
        return;
    }
    Node query(int rt,int l,int r,int ql,int qr){
        if (ql <= l && r <= qr){
            return nodes[rt];
        }
        int mid = l+r>>1;
        pd(rt);
        if (ql > mid){
            return query(rs,mid+1,r,ql,qr);
        }else if (qr < mid + 1){
            return query(ls,l,mid,ql,qr);
        }else{
            return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
        }
    }
};
```
区间乘法\&加法:
```cpp
class SegTree_plus_mul{
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    struct Node{
        ll sum,plus,mul,len;
    };
    private:
        Node nodes[8000000];
    public:
        ll mod;
        Node merge(Node A,Node B){
            Node C;
            C.plus = 0;
            C.mul = 1;
            C.sum = (A.sum + B.sum) % mod;
            C.len = A.len + B.len;
            return C;
        }
        void build(ll rt,ll l,ll r){
            if (l==r){
                cin >> nodes[rt].sum;
                nodes[rt].len = 1;
                nodes[rt].plus = 0;
                nodes[rt].mul = 1;
                return;
            }
            ll mid = l+r>>1;
            build(ls,l,mid),build(rs,mid+1,r);
            nodes[rt] = merge(nodes[ls],nodes[rs]);
        }
        void pushDown(int rt){
            nodes[rs].sum = (nodes[rs].sum*nodes[rt].mul%mod+nodes[rt].plus*nodes[rs].len%mod) % mod;
            nodes[ls].sum = (nodes[ls].sum*nodes[rt].mul%mod+nodes[rt].plus*nodes[ls].len%mod) % mod;

            nodes[rs].mul = (nodes[rs].mul*nodes[rt].mul) % mod;
            nodes[ls].mul = (nodes[ls].mul*nodes[rt].mul) % mod;

            nodes[rs].plus = (nodes[rs].plus*nodes[rt].mul+nodes[rt].plus) % mod;
            nodes[ls].plus = (nodes[ls].plus*nodes[rt].mul+nodes[rt].plus) % mod;

            nodes[rt].plus = 0;
            nodes[rt].mul = 1;
        }
        // mode 1 is plus,mode 2 is mul.
        void update(ll rt,ll l,ll r,ll ql,ll qr,ll mode,ll k){
            if (ql <= l && r <= qr){
                if (mode == 1){
                    nodes[rt].plus += k;
                    nodes[rt].plus %= mod;
                    nodes[rt].sum += (k * nodes[rt].len) % mod;
                    nodes[rt].sum %= mod;
                }else{
                    nodes[rt].plus *= k;
                    nodes[rt].plus %= mod;
                    nodes[rt].mul *= k;
                    nodes[rt].mul %= mod;
                    nodes[rt].sum *= k;
                    nodes[rt].sum %= mod;
                }
                return;
            }
            pushDown(rt);
            ll mid = l+r>>1;
            if (ql<=mid){
                update(ls,l,mid,ql,qr,mode,k);
            }
            if (qr >= mid+1){
                update(rs,mid+1,r,ql,qr,mode,k);
            }
            nodes[rt] = merge(nodes[ls],nodes[rs]);
        }
        Node query(ll rt,ll l,ll r,ll ql,ll qr){
            if (ql <= l && r <= qr){
                return nodes[rt];
            }
            pushDown(rt);
            ll mid = l+r>>1;
            if (qr<=mid){
                return query(ls,l,mid,ql,qr);
            }else if (ql>=mid+1){
                return query(rs,mid+1,r,ql,qr);
            }else{
                return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
            }
        }
};
```

### 动态开点线段树

```cpp
class Dynamic_SegTree{
public:
    int idx[N],n;
    struct Node{
        // 补充需要维护的量
        int ls,rs,siz,laz;
        Node(){

        }
    }nodes[N];
    int cnt;

    void init(int N){
        n = N;
        cnt = 0;
        for (int i = 1;i<n+1;i++){
            idx[i] = 0;
        }
    }

    int new_node(){
        ++cnt;
        // 初始化节点

        return cnt;
    }

    Node merge(Node L,Node R){
        Node M;M.ls = M.rs = 0;
        M.laz = 0;M.siz = L.siz + R.siz;
        // 补充合并方法

        return M;
    }

    void pushDown(int rt){
        
    }

    Node query(int& rt,int l,int r,int ql,int qr){
        if (!rt){
            return Node();
        }
        if (ql <= l && r <= qr){
            return nodes[rt];
        }

        pushDown(rt);

        int mid = l + r >> 1;
        if (ql >= mid + 1){
            return query(nodes[rt].rs,mid + 1,r,ql,qr);
        }else if (qr <= mid){
            return query(nodes[rt].ls,l,mid,ql,qr);
        }else{
            return merge(query(nodes[rt].rs,mid + 1,r,ql,qr),query(nodes[rt].ls,l,mid,ql,qr));
        }
    }

    void pushUp(int rt){
        // 补充
        nodes[rt].siz = 1;
        if (nodes[rt].ls){
            nodes[rt].siz += nodes[nodes[rt].ls].siz;
        }

        if (nodes[rt].rs){
            nodes[rt].siz += nodes[nodes[rt].rs].siz;
        }

        return;
    }

    void update(int& rt,int l,int r,int ql,int qr){
        if (!rt){
            rt = new_node();
        }
        if (ql <= l && r <= qr){
            // 补充更新方法
            return;
        }

        pushDown(rt);

        int mid = l + r >> 1;
        if (ql <= mid){
            update(nodes[rt].ls,l,mid,ql,qr);
        }
        if (qr >= mid + 1){
            update(nodes[rt].rs,mid + 1,r,ql,qr);
        }

        pushUp(rt);
        return;
    }

    int Tree_merge(int u,int v,int l,int r){
        if (!u || !v) return u | v;
        if (l == r){
            // 补充叶节点合并方法
            return u;
        }
        if (nodes[u].siz < nodes[v].siz){
            swap(u,v);
        }
        int mid = l + r >> 1;
        nodes[u].ls = Tree_merge(nodes[u].ls,nodes[v].ls,l,mid);
        nodes[u].rs = Tree_merge(nodes[u].rs,nodes[v].rs,mid+1,r);
        pushUp(u);
        return u;
    }
};

```

### 树状数组

```cpp
struct FenwickTree{
    ll c[N];
    int n;
    ll lowbit(ll x) {return x & -x;}
    void update(ll x,ll v){while (x<=n) c[x] += v,x += x & -x;}
    int query(ll x){ll ans = 0;while (x) ans += c[x],x -= x & -x;return ans;}
    int query(ll l,ll r) {return query(r) - query(l-1);}
};
```

### 左偏树

```cpp
class left_leaning_heap{
public:
    #define ls(x) nodes[x].ls
    #define rs(x) nodes[x].rs
    struct Node{
        int fa,dist,ls,rs,val,laz;
        bool operator<(const Node& A) const{
            return val > A.val;
        }
    }nodes[N];

    left_leaning_heap(){
        nodes[0].dist = -1;
    }

    int find(int x){
        if (x == nodes[x].fa){
            return x;
        }
        return nodes[x].fa = find(nodes[x].fa);
    }

    void pushUp(int x){
        nodes[x].dist = nodes[ls(x)].dist + 1;
        nodes[ls(x)].fa = nodes[rs(x)].fa = x;
    }

    int merge(int x,int y){
        if (!x || !y) return x | y;

        if (nodes[x] < nodes[y]){
            swap(x,y);
        }

        nodes[x].rs = merge(nodes[x].rs,y);
        if (nodes[ls(x)].dist < nodes[rs(x)].dist){
            swap(ls(x),rs(x));
        }

        pushUp(x);
        return x;
    }

    void erase(int x){
        nodes[x].fa = nodes[ls(x)].fa = nodes[rs(x)].fa = merge(ls(x),rs(x));
        nodes[x].dist = nodes[x].ls = nodes[x].rs = 0;
    }
};
```

### Splay

```cpp
class Splay{
public:
    int rt,tot;
    struct Node{
        int val,cnt,fa,ch[2],siz;
    }nodes[N];
    
    int newNode(int x){
        ++tot;
        nodes[tot].val = x;
        nodes[tot].cnt = nodes[tot].siz = 1;
        nodes[tot].fa = nodes[tot].ch[0] = nodes[tot].ch[1] = 0;
        return tot;
    }

    void init(){
        tot = 0;
        newNode(-INT_MAX);newNode(INT_MAX);
        rt = 1;
        nodes[rt].siz = 2;
        nodes[rt].ch[1] = 2;
        nodes[2].fa = rt;
        return;
    }

    void update(int x){
        nodes[x].siz = nodes[nodes[x].ch[0]].siz + nodes[nodes[x].ch[1]].siz + nodes[x].cnt;
    }

    void rot_left(int x){
        int y = nodes[x].fa,z = nodes[y].fa;
        nodes[y].ch[1] = nodes[x].ch[0];nodes[nodes[x].ch[0]].fa = y;
        nodes[x].ch[0] = y;nodes[y].fa = x;
        nodes[z].ch[nodes[z].ch[1] == y] = x;nodes[x].fa = z;
        update(y),update(x);
    }

    void rot_right(int x){
        int y = nodes[x].fa,z = nodes[y].fa;
        nodes[y].ch[0] = nodes[x].ch[1];nodes[nodes[x].ch[1]].fa = y;
        nodes[x].ch[1] = y;nodes[y].fa = x;
        nodes[z].ch[nodes[z].ch[1] == y] = x;nodes[x].fa = z;
        update(y),update(x);
    }

    int getlr(int x){
        return nodes[nodes[x].fa].ch[1] == x;
    }

    void rotate(int x){
        if (getlr(x)){
            rot_left(x);
        }else{
            rot_right(x);
        }
    }

    void splay(int x,int target){
        if (!target){
            rt = x;
        }
        while (nodes[x].fa != target){
            int y = nodes[x].fa,z = nodes[y].fa ;
            if (z != target){
                if (getlr(x) == getlr(y)){
                    rotate(y);
                }else{
                    rotate(x);
                }
            }
            rotate(x);
        }
        return;
    }

    void find(int x){
        if (!rt) return;
        int p = rt;
        while (nodes[p].val != x && nodes[p].ch[x > nodes[p].val]){
            p = nodes[p].ch[x > nodes[p].val];
        }
        splay(p,0);
    }

    int pre(int x){
        find(x);
        if (nodes[rt].val < x){
            return rt;
        }
        int p = nodes[rt].ch[0];
        while (nodes[p].ch[1]){
            p = nodes[p].ch[1];
        }
        splay(p,0);
        return p;
    }

    int suc(int x){
        find(x);
        if (nodes[rt].val > x){
            return rt;
        }
        int p = nodes[rt].ch[1];
        while (nodes[p].ch[0]){
            p = nodes[p].ch[0];
        }
        splay(p,0);
        return p;
    }

    void insert(int x){
        int p = rt,fp = nodes[p].fa;
        while (p && nodes[p].val != x){
            fp = p;p = nodes[p].ch[x > nodes[p].val];
        }
        if (!p){
            p = newNode(x);
            nodes[fp].ch[x > nodes[fp].val] = p;
            nodes[p].fa = fp;
        }else{
            nodes[p].cnt++;
        }
        splay(p,0);
    }

    void del(int x){
        int xPre = pre(x),xSuc = suc(x);
        splay(xPre,0);splay(xSuc,xPre);
        int d = nodes[xSuc].ch[0];
        if (--nodes[d].cnt){
            splay(d,0);
        }else{
            nodes[xSuc].ch[0] = 0;
            update(xSuc);update(xPre);
        }
    }

    int kth(int x){
        int p = rt;
        while (1){
            int v = nodes[p].ch[0];
            if (nodes[v].siz + nodes[p].cnt < x){
                x -= nodes[v].siz + nodes[p].cnt;
                p = nodes[p].ch[1];
            }else{
                if (nodes[v].siz < x){
                    splay(p,0);
                    return p;
                }else{
                    p = v;
                }
            }
        }
    }

    int getRank(int x){
        find(x);
        return nodes[nodes[rt].ch[0]].siz;
    }
};
```

### 并查集

```cpp
class Dsu{
public:
    int fa[N];
    void init(int n){
        for (int i = 1;i<n+1;i++){
            fa[i] = i;
        }
    }
    int find(int x){
        if (x == fa[x]){
            return x;
        }
        return fa[x] = find(fa[x]);
    }
    void merge(int x,int y){
        x = find(x),y = find(y);
        if (x == y){
            return;
        }
        fa[x] = y;
        return;
    }
};
```

## 几何

### 凸包

```cpp
/*
使用说明:
手动输入点的数量n,各个点的坐标,然后init即可找出凸包.
可以处理重点,不会出现三点共线的问题.
默认double.
使用极角排序的方式寻找凸包.
*/

struct Point {
    double x, y;
	int idx;
    Point(double X = 0, double Y = 0) {
        x = X;
        y = Y;
    }

    Point operator-(const Point& A) const {
        return Point(x - A.x, y - A.y);
    }

    Point operator+(const Point& A) const{
        return Point(x + A.x,y + A.y);
    }

    double operator^(const Point& A) const {
        return x * A.y - A.x * y;
    }

    double operator*(const Point& A) const {
        return x * A.x + y * A.y;
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    double len2() {
        return x * x + y * y;
    }

    bool operator==(const Point& A) const {
        return (x == A.x) && (y == A.y);
    }
} ;

class ConvexHull {
public:
    int n;
	bool vis[N];
    Point points[N], hull[N];
    static bool cmp_y(const Point& A, const Point& B) {
		if (A.y == B.y){
			return A.x < B.x;
		}
        return A.y < B.y;
    }

    static bool cmp_sita(const Point& A, const Point& B, const Point& base) {
        Point A_base = A - base;
        Point B_base = B - base;
        if ((A_base ^ B_base) == 0) {
            return A_base.len() > B_base.len();
        }
        return (A_base ^ B_base) < 0;
    }

    int tp;

    void init() {
        tp = 1;
        sort(points + 1, points + 1 + n, cmp_y);
        hull[1] = points[1];
        sort(points + 2, points + 1 + n, [&base = hull[1]](const Point& A, const Point& B) { return cmp_sita(A, B, base); });
        int cur = 2;
        for (; cur <= n; cur++) {
            if (points[cur] == hull[1]) continue;
            else { hull[++tp] = points[cur]; break;}
        }
        for (cur++; cur <= n; cur++) {
			if (hull[tp] == points[cur]) continue;
            Point L = hull[tp] - hull[tp - 1];
            Point R = points[cur] - hull[tp];
            if (R.x == 0 && R.y == 0) continue;
            if ((L ^ R) > 0) {
				while ((L ^ R) >= 0 && tp > 1){
					if ((L ^ R) == 0){
						if ((L * R) < 0){
							break;
						}else{
							--tp;break;
						}
					}
					tp--;
					L = hull[tp] - hull[tp - 1];
					R = points[cur] - hull[tp];
				}
                hull[++tp] = points[cur];
            } else if ((L ^ R) < 0) {
                hull[++tp] = points[cur];
            } else {
                if ((L * R) < 0) {
                    continue;
                } else {
                    hull[tp] = points[cur];
                }
            }
        }
    }
} ;
```

### 三角形

```cpp
/*
使用说明:
手动输入Triangle中三个点的坐标
update函数更新外心左边和外接圆半径
可以应对三点共线的特殊情况
*/

struct Point {
    double x, y;
	int idx;
    Point(double X = 0, double Y = 0) {
        x = X;
        y = Y;
    }

    Point operator-(const Point& A) const {
        return Point(x - A.x, y - A.y);
    }

    Point operator+(const Point& A) const{
        return Point(x + A.x,y + A.y);
    }

    double operator^(const Point& A) const {
        return x * A.y - A.x * y;
    }

    double operator*(const Point& A) const {
        return x * A.x + y * A.y;
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    double len2() {
        return x * x + y * y;
    }

    bool operator==(const Point& A) const {
        return (x == A.x) && (y == A.y);
    }
};

class Triangle{
public:
    Point nodes[3];
    Point circumCenter;
    double r;
    void update(){
        double a,b,c,d,e,f;
        a=nodes[1].x-nodes[0].x,b=nodes[1].y-nodes[0].y,c=nodes[2].x-nodes[1].x;
        d=nodes[2].y-nodes[1].y;e=nodes[1].x*nodes[1].x+nodes[1].y*nodes[1].y
        -nodes[0].x*nodes[0].x-nodes[0].y*nodes[0].y;
        f=nodes[2].x*nodes[2].x+nodes[2].y*nodes[2].y-nodes[1].x*nodes[1].x
        -nodes[1].y*nodes[1].y;
        if (a*d == c*b){
            r = 0;
            if ((nodes[0] - nodes[1]).len() > r){
                r = (nodes[0] - nodes[1]).len();
                circumCenter = nodes[0] + nodes[1];
                circumCenter.x /= 2,circumCenter.y /= 2;
            }
            if ((nodes[0] - nodes[2]).len() > r){
                r = (nodes[0] - nodes[2]).len();
                circumCenter = nodes[0] + nodes[2];
                circumCenter.x /= 2,circumCenter.y /= 2;
            }
            if ((nodes[2] - nodes[1]).len() > r){
                r = (nodes[2] - nodes[1]).len();
                circumCenter = nodes[2] + nodes[1];
                circumCenter.x /= 2,circumCenter.y /= 2;
            }
            return;
        }
        circumCenter.x=(f*b-e*d)/(c*b-a*d)/2;
        circumCenter.y=(a*f-e*c)/(a*d-b*c)/2;
        r=(nodes[0]-circumCenter).len();
        return;
    }
};
```

## 数学

### 组合数
```cpp
class CombinationNumber{
public:
    ll fact[MAXN];    
    ll inv[MAXN];
    ll quick(ll base, ll k) {
        ll res = 1;
        while (k) {
            if (k & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            k >>= 1;
        }
        return res;
    }     

    void precompute() {
        fact[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        inv[MAXN - 1] = quick(fact[MAXN - 1], MOD - 2); 
        for (int i = MAXN - 2; i >= 0; i--) {
            inv[i] = inv[i + 1] * (i + 1) % MOD; 
        }
    }   

    ll C(ll n, ll m) {
        if (m > n || m < 0) {
            return 0;
        }
        return fact[n] * inv[m] % MOD * inv[n - m] % MOD; 
    } 

    void init(){
        precompute();
    }
};
```

### 矩阵
```cpp
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
```

### NTT
```cpp
const int MAXN = 3 * 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;
class PolynomialMultiplier {
public:
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int N, M, limit = 1, L;
    int r[MAXN];
    long long a[MAXN], b[MAXN];

    inline long long fastPow(long long a, long long k) {
        long long base = 1;
        while(k) {
            if(k & 1) base = (base * a) % P;
            a = (a * a) % P;
            k >>= 1;
        }
        return base % P;
    }

    inline void NTT(long long *A, int type) {
        for(int i = 0; i < limit; i++)
            if(i < r[i]) swap(A[i], A[r[i]]);
        for(int mid = 1; mid < limit; mid <<= 1) {
            long long Wn = fastPow(type == 1 ? G : Gi, (P - 1) / (mid << 1));
            for(int j = 0; j < limit; j += (mid << 1)) {
                long long w = 1;
                for(int k = 0; k < mid; k++, w = (w * Wn) % P) {
                    int x = A[j + k], y = w * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P,
                    A[j + k + mid] = (x - y + P) % P;
                }
            }
        }
        if(type == -1) {
            long long inv = fastPow(limit, P - 2);
            for(int i = 0; i < limit; i++) A[i] = A[i] * inv % P;
        }
    }

public:
    PolynomialMultiplier() {
        for(int i = 0; i < MAXN; i++) r[i] = 0;
        for(int i = 0; i < MAXN; i++) a[i] = 0;
        for(int i = 0; i < MAXN; i++) b[i] = 0;
    }

    vector<int> multiply(vector<int> &A, vector<int> &B) {
        N = A.size() - 1;
        M = B.size() - 1;
        copy(A.begin(), A.end(), a);
        copy(B.begin(), B.end(), b);

        while(limit <= N + M) limit <<= 1, L++;
        for(int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));

        NTT(a, 1);
        NTT(b, 1);
        for(int i = 0; i < limit; i++) a[i] = (a[i] * b[i]) % P;
        NTT(a, -1);

        vector<int> result(N + M + 1);
        for(int i = 0; i <= N + M; i++) result[i] = a[i] % P;

        return result;
    }
};

```

### 素数筛
```cpp
class Primes{
public:
    ll notPrime[N];
    vector<ll> primes;
    void sieve(){
        for (ll i = 2;i<2e6;i++){
            if (!notPrime[i]){
                primes.push_back(i);
                for (int j = i*2;j<2e6;j+=i){
                    notPrime[j] = 1;
                }
            }
        }
        return;
    }
};
```

### 随机数
```cpp
class RandomNumberGenerator{
public:
    RandomNumberGenerator() : gen(std::random_device{}()){}

    ll generate(ll l,ll r){
        uniform_int_distribution<> dis(l,r);
        return dis(gen);
    }
private:
    mt19937 gen;
};
```

### 勾股数
```cpp
/*
It is usd to find the base-pythagoras.
*/
typedef long long ll;
class Pythagoras{
public:
    vector<tuple<int,int,int>> q;
    int maxN;
    Pythagoras(int MAXN){
        maxN = MAXN;
    }
    void init(){
        for (int i = 1;i<=maxN;i++){
            for (int j = i+1;2*i*j<=maxN && j*j+i*i<=maxN;j++){
                ll a = j * j - i * i;
                ll b = 2 * i * j;
                ll c = j * j + i * i;
                if (b > c){
                    swap(b,c);
                }
                if (a > b){
                    swap(a,b);
                }
                if (__gcd(a,b) == 1){
                    for (int k = 1;k*c<=maxN;k++){
                        q.emplace_back(a*k,b*k,c*k);
                    }
                }
            }
        }
    }
};
```

## 图论

### 邻接表
```cpp
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
```

### LCA(倍增)
```cpp
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
```

### 树链剖分
```cpp
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
```
