#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegTree{
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