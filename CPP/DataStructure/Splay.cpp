#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2000000;

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