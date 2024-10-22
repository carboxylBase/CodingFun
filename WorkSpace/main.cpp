#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = 3.1415926;
double r;
double c=10000;
int n,m;
void solve()
{
    cin >> n >> m;
    r = c / 2 / PI;
    double sita1,sita2;
    sita1 = 2*PI/n;
    sita2 = 2*PI/(n+m);
    double sita = 0;
    for (int i = 1,j=1;i<=n-1;i++){
        while (abs((j+1)*sita2-sita1*i)<abs(j*sita2-sita1*i)){
            j++;
        }
        sita += abs(j*sita2-sita1*i);
    }
    cout<<setprecision(4)<<fixed<<sita*r<<endl;
    return;
}
int main()
{
   // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(0);
    int t = 1;
    //  cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}