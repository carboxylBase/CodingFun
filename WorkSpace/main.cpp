#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
using namespace std;
#define int long long
typedef long long ll;
const double PI = 3.1415926;
struct Point{
    double x,y;
    Point(double X = 0,double Y = 0){
        x = X,y = Y;
    }
    Point operator-(const Point& A){
        return Point(x-A.x,y-A.y);
    }
    double operator^(const Point& A){
        return x*A.y-A.x*y;
    }
    double dis(){
        return pow(x*x+y*y,0.5);
    }
}point[2000000];
Point q[2000000];
int tp;
bool cmp(Point A,Point B){
    Point a = A - point[1];
    Point b = B - point[1];
    if ((a^b) < 0){
        return 1;
    }else if (abs(a^b)<=0.000001){
        return a.dis() < b.dis();
    }
    return 0;
}
bool cmp1(Point A,Point B){
    if (A.y != B.y)
        return A.y < B.y;
    return A.x < B.x;
}
bool cmp2(Point A,Point B){
    if (A.x != B.x)
        return A.x < B.x;
    return A.y < B.y;
}
void solve()
{
    int n,l;
    cin >> n >>l;
    for (int i = 1;i<=n;i++){
        cin >> point[i].x >> point[i].y;
    }
    sort(point+1,point+1+n,cmp1);
    sort(point+1+1,point+1+n,cmp);
    q[++tp] = point[1];
    q[++tp] = point[2];
    for (int i = 3;i<n+1;i++){
        int l = 2,r = tp,mid,ans=1;
        bool ok = 1;
        while (l<=r){
            mid = l + r >> 1;
            Point a = (q[mid] - q[mid-1]);
            Point b = point[i] - q[mid];
            if ((b^a)>=0){
                ans = mid;
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        if (!ok){
            continue;
        }
        tp = ans + 1;
        q[tp] = point[i];
    }
    double ans = 0;
    // cout<<tp<<endl;
    for (int i = 1;i<=tp-1;i++){
        ans +=(q[i+1]-q[i]).dis();
    }
    ans += (q[tp] - q[1]).dis();
    // ans += 2*PI*l;
    cout << (ll)(ans+0.5);
    return;
}
signed main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}