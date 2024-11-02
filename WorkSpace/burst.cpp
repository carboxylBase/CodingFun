#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const double PI = 3.1415926;
struct Point {
    int x, y,inde;
    Point(int X = 0, int Y = 0) {
        x = X, y = Y;
    }
    Point operator-(const Point& A) {
        return Point(x - A.x, y - A.y);
    }
    int operator^(const Point& A) {
        return x * A.y - A.x * y;
    }
    double dis() {
        return pow(x * x + y * y,0.5);
    }
    ll dis2() {
        return x * x + y * y;
    }
};
bool cmp(Point& A, Point& B,Point& C) {
    Point a = A - C;
    Point b = B - C;
    if ((a ^ b) < 0) {
        return 1;
    } else if (abs(a ^ b) <= 0) {
        return a.dis() < b.dis();
    }
    return 0;
}
bool cmp1(Point A, Point B) {
    if (A.y != B.y)
        return A.y < B.y;
    return A.x < B.x;
}
class ConvexHull{
    public:
        vector<Point> q;
        vector<Point> hull;
        void add(Point p){
            q.push_back(p);
        }
        vector<Point> st;
        int tp = 0;
        void findHull(){
            sort(q.begin(),q.end(),[&](Point& A,Point& B){
                return cmp1(A,B);
            });
            sort(q.begin()+1,q.end(),[&](Point& A,Point& B){
                return cmp(A,B,q[0]);
            });
            st.resize(q.size()*2);
            st[tp++] = q[0],st[tp] = q[1]; 
            for (int i = 2;i<q.size();i++){
                int l = 1, r = tp, mid, ans = 1;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    Point a = st[mid] - st[mid - 1];
                    Point b = q[i] - st[mid];
                    if ((b ^ a) >= 0) {
                        ans = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                tp = ans + 1;
                st[tp] = q[i];
            }
        }
        double C(){
            double sum = 0;
            for (int i = 0;i<=tp-1;i++){
                sum += (st[i+1]-st[i]).dis();
            }
            sum += (st[0]-st[tp]).dis();
            return sum;
        }
        //注意，这个返回的是二倍面积。
        ll S(){
            ll sum = 0;
            for (int i = 2;i<q.size();i++){
                sum += abs((st[i]-st[0])^(st[i-1]-st[0]));
            }
            return sum;
        }
};

void solve()
{
    ConvexHull solver;
    int n,L;
    cin >> n >> L;
    for (int i = 1;i<n+1;i++){
        int x,y;
        cin >> x >> y;
        solver.add(Point(x,y));
    }
    solver.findHull();
    double ans = 0;
    ans = solver.C();
    ans += 2*PI*L;
    // cout<<ans<<endl;
    cout<<(ll)(ans+0.5);
    return;
}
signed main()
{
    // reopen("input.txt", "r", stdin);
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