#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const double PI = 3.1415926;
struct Point {
    ll x, y,inde;
    Point(ll X = 0, ll Y = 0) {
        x = X, y = Y;
    }
    Point operator-(const Point& A) {
        return Point(x - A.x, y - A.y);
    }
    ll operator^(const Point& A) {
        return x * A.y - A.x * y;
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
        return a.dis2() < b.dis2();
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
        __int128 tp = 0;
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
                __int128 l = 1, r = tp, mid, ans = 1;
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
                sum += (st[i+1]-st[i]).dis2();
            }
            sum += (st[0]-st[tp]).dis2();
            return sum;
        }
        //注意，这个返回的是二倍面积。
        __int128 S(){
            __int128 sum = 0;
            for (int i = 2;i<q.size();i++){
                __int128 s = (st[i]-st[0])^(st[i-1]-st[0]);
                if (s<0){
                    s = -s;
                }
                sum += s;
            }
            return sum;
        }
};