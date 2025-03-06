#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2000000;

struct FenwickTree{
    ll c[N];
    int n;
    ll lowbit(ll x) {return x & -x;}
    void update(ll x,ll v){while (x<=n) c[x] += v,x += x & -x;}
    int query(ll x){ll ans = 0;while (x) ans += c[x],x -= x & -x;return ans;}
    int query(ll l,ll r) {return query(r) - query(l-1);}
};
