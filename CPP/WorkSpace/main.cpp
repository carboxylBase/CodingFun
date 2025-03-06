// It's a wonderful life.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;
const ll MOD = 998244353;
const ll MAX = 1e18;

int dp[2000][2000];

int find(int x,int y){
	if (dp[x][y]){
		return dp[x][y];
	}
	if (x == 0 && y == 0){
		return 2;
	}
	if (x == 0 || y == 0){
		return 1;
	}
	for (int i = 1;i<x+1;i++){
		if (find(x - i,y) == 2){
			return dp[x][y] = dp[y][x] = 1;
		}
	}
	for (int i = 1;i<y+1;i++){
		if (find(x,y - i) == 2){
			return dp[x][y] = dp[y][x] = 1;
		}
	}
	for (int i = 1;i<=min(x,y);i++){
		if (find(x - i,y - i) == 2){
			return dp[x][y] = dp[y][x] = 1;
		}
	}
	return dp[x][y] = dp[y][x] = 2;
}
bool vis[N];
void solve(){
	ll a,b;cin >> a >> b;
	if (a > b) swap(a,b);

	b -= a;
	b--;
	ll c = 1;
	vector<ll> d = {2 ,1 ,2 ,2 ,1 ,2 ,1 ,2 ,2 ,1 ,2 ,2 ,1 };
	ll sumD = 0;
	for (int i = 0;i<d.size();i++)
	{
		sumD += d[i];
	}
	c += b / d.size() * sumD;
	b %= d.size();
	for (int i = 0;i<b;i++){
		c += d[i];
	}

	if (c == a){
		cout << 0;
	}else{
		cout << 1;
	}
    return;
}

signed main(){
	freopen("input.txt","r",stdin);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--){
        solve();
    }
    return 0;
}