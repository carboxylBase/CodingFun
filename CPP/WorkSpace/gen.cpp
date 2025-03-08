// It's a wonderful life.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;
const ll MOD = 998244353;
const ll MAX = 1e18;

void tree(){

}

void solve(){
    srand(time(0));
    int n,k;
    n = rand() % 10 + 1;
    k = rand() % n + 1;
    cout << n << " " << k << endl;
    for (int i = 1;i<n+1;i++){
        cout << rand() % 10 + 1 << " ";
    }
    return;
}

signed main(){
    // freopen("input.txt","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--){
        solve();
    }
    return 0;
}
