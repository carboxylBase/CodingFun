#include<bits/stdc++.h>
using namespace std;

template <typename T, typename S> T floor(T x, S y) {
  assert(y);
  return (y < 0 ? floor(-x, -y) : (x > 0 ? x / y : x / y - (x % y == 0 ? 0 : 1)));
}

int main(){
  cin.tie(0) -> sync_with_stdio(false);
  cout.tie(0);
  
  long long n, m;
  cin >> n >> m;
  
  long long sum = 0, mi = 1e10, mx = 0;
  for(int i = 1; i <= n; i ++){
    long long a;
    cin >> a;
    sum += a, mi = min(mi, a), mx = max(mx, a);
  }
  
  if(sum % __gcd(n, m)){
    cout << -1;
    return 0;
  }
  
  long long  y = mi;
  if(n != m){
    y = min({y, floor(sum - mx * m, n - m)});
  }else{
    if(mx * m - sum > 0){
      cout << -1;
      return 0;
    }
  }
  
  long long x = (sum - n * y) / m;
  while((sum - m * x) % n) ++ x;
  cout << x;
  
  return 0;
}