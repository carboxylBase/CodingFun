#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;

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
