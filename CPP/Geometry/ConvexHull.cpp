#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const ll N = 2000000;

/*
使用说明:
手动输入点的数量n,各个点的坐标,然后init即可找出凸包.
可以处理重点,不会出现三点共线的问题.
默认double.
使用极角排序的方式寻找凸包.
*/

struct Point {
    double x, y;
	int idx;
    Point(double X = 0, double Y = 0) {
        x = X;
        y = Y;
    }

    Point operator-(const Point& A) const {
        return Point(x - A.x, y - A.y);
    }

    Point operator+(const Point& A) const{
        return Point(x + A.x,y + A.y);
    }

    double operator^(const Point& A) const {
        return x * A.y - A.x * y;
    }

    double operator*(const Point& A) const {
        return x * A.x + y * A.y;
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    double len2() {
        return x * x + y * y;
    }

    bool operator==(const Point& A) const {
        return (x == A.x) && (y == A.y);
    }
} ;

class ConvexHull {
public:
    int n;
	bool vis[N];
    Point points[N], hull[N];
    static bool cmp_y(const Point& A, const Point& B) {
		if (A.y == B.y){
			return A.x < B.x;
		}
        return A.y < B.y;
    }

    static bool cmp_sita(const Point& A, const Point& B, const Point& base) {
        Point A_base = A - base;
        Point B_base = B - base;
        if ((A_base ^ B_base) == 0) {
            return A_base.len() > B_base.len();
        }
        return (A_base ^ B_base) < 0;
    }

    int tp;

    void init() {
        tp = 1;
        sort(points + 1, points + 1 + n, cmp_y);
        hull[1] = points[1];
        sort(points + 2, points + 1 + n, [&base = hull[1]](const Point& A, const Point& B) { return cmp_sita(A, B, base); });
        int cur = 2;
        for (; cur <= n; cur++) {
            if (points[cur] == hull[1]) continue;
            else { hull[++tp] = points[cur]; break;}
        }
        for (cur++; cur <= n; cur++) {
			if (hull[tp] == points[cur]) continue;
            Point L = hull[tp] - hull[tp - 1];
            Point R = points[cur] - hull[tp];
            if (R.x == 0 && R.y == 0) continue;
            if ((L ^ R) > 0) {
				while ((L ^ R) >= 0 && tp > 1){
					if ((L ^ R) == 0){
						if ((L * R) < 0){
							break;
						}else{
							--tp;break;
						}
					}
					tp--;
					L = hull[tp] - hull[tp - 1];
					R = points[cur] - hull[tp];
				}
                hull[++tp] = points[cur];
            } else if ((L ^ R) < 0) {
                hull[++tp] = points[cur];
            } else {
                if ((L * R) < 0) {
                    continue;
                } else {
                    hull[tp] = points[cur];
                }
            }
        }
    }
} ;