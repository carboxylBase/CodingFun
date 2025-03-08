// It's a wonderful life.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;
const ll MOD = 998244353;
const ll MAX = 1e18;
#define int ll
/*
使用说明:
首先调用 init 函数初始化 ax + by = c 的参数,返回 0 表示无解.
cal 函数计算特解,通解为 X1 + k * dx , Y1 + k * dy
*/ 
class exGcd{
public:
    int a,b,dx,dy,c,gcd_ab;
    int X0,Y0,X1,Y1;
    bool init(int A,int B,int C = 0){
        a = A,b = B,c = C;
        gcd_ab = __gcd(a,b);
        if (c % gcd_ab != 0){
            return 0;
        }
        return 1;
    }
    void exgcd(int a,int b){
        if (b == 0){
            X0 = 1;
            Y0 = 0;
        }else{
            exgcd(b,a % b);
            X1 = X0,Y1 = Y0;
            X0 = Y1;
            Y0 = X1 - a / b * Y1; 
        }
        return;
    }
    void cal(){
        exgcd(a,b);
        X1 = X0 * c / gcd_ab;
        Y1 = Y0 * c / gcd_ab;
        dx = b / gcd_ab;
        dy = -a / gcd_ab; 
        return;
    }
}solver;

int getAns(double x){
    int res = 0;
    if (solver.dx > 0){
        res = ceil(double(x - solver.X1) / solver.dx);
    }else{
        res = floor(double(x - solver.X1) / solver.dx);
    }
    return solver.X1 + res * solver.dx;
}

int n,a[N],sum,k;

void solve(){
    cin >> n >> k;
    int mx = -MAX;
    int mn = MAX;
    for (int i = 1;i<n+1;i++){
        cin >> a[i];
        sum += a[i];
        mn = min(mn,a[i]);
        mx = max(a[i],mx);
    }

    if (mn == mx){
        cout << 0 << endl;
        return;
    }

    if (solver.init(k,n,sum) == 0){
        cout << -1;
        return;
    }

    solver.cal();

    if (n == k){
        cout << -1;
        return;
    }
    
    int ans = max(getAns(double(sum - n * mn) / k),getAns(double(n * mx - sum) / (n - k)));
    cout << ans;
    return;
}

signed main(){
    // freopen("input.txt","r",stdin);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--){
        solve();
    }
    return 0;
}
