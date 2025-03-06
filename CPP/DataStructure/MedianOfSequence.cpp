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