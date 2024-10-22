#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct Mat
{
    int n, m;
    T **a;
    Mat(int _n = 0, int _m = 0) : n(_n), m(_m)
    {
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memset(a[i], 0, sizeof(T) * m);
    }
    Mat(const Mat &B)
    {
        n = B.n, m = B.m;
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memcpy(a[i], B.a[i], sizeof(T) * m);
    }
    ~Mat() { delete[] a; }
    Mat &operator=(const Mat &B)
    {
        delete[] a;
        n = B.n, m = B.m;
        a = new T *[n];
        for (int i = 0; i < n; i++)
            a[i] = new T[m], memcpy(a[i], B.a[i], sizeof(T) * m);
        return *this;
    }
    Mat operator+(const Mat &B) const
    { 
        assert(n == B.n && m == B.m);
        Mat ret(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ret.a[i][j] = (a[i][j] + B.a[i][j]) % mod;
        return ret;
    }
    Mat &operator+=(const Mat &B) { return *this = *this + B; }
    Mat operator*(const Mat &B) const
    {
        Mat ret(n, B.m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < B.m; ret.a[i][j++] %= mod)
                for (int k = 0; k < m; ++k)
                    ret.a[i][j] += a[i][k] * B.a[k][j] % mod;
        return ret;
    }
    Mat &operator*=(const Mat &B) { return *this = *this * B; }
};
Mat<int> qpow(Mat<int> A, int b)
{
    Mat<int> ret(A);
    for (--b; b; b >>= 1, A *= A)
        if (b & 1)
            ret *= A;
    return ret;
}