#include<bits/stdc++.h>
using namespace std;
const static void fast_io() { ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); }
#define endl '\n'
#define int long long
const int mod=1e9+7;
int ksm(int a,int b){
    int res=1%mod;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int inv(int x){ return ksm(x,mod-2); }
int sum(int x){
    x=x%mod;
    return (x*(x+1)/2)%mod;
}
void solve(){
    int n;
    cin>>n;
    int m=4 * n - 4;
    int ans=0;
    ans+=(sum(n*n)-sum(m)+mod)%mod*4%mod;
    ans+=(sum(m)-sum(4)+mod)%mod*3%mod;
    ans+=sum(4) * 2;
    ans%=mod;
    cout<<ans<<endl;
}
signed main(){
    freopen("input.txt","r",stdin);
    fast_io();
    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }   
    return 0;
}