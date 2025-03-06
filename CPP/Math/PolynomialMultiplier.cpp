#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 3 * 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;
class PolynomialMultiplier {
public:
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int N, M, limit = 1, L;
    int r[MAXN];
    long long a[MAXN], b[MAXN];

    inline long long fastPow(long long a, long long k) {
        long long base = 1;
        while(k) {
            if(k & 1) base = (base * a) % P;
            a = (a * a) % P;
            k >>= 1;
        }
        return base % P;
    }

    inline void NTT(long long *A, int type) {
        for(int i = 0; i < limit; i++)
            if(i < r[i]) swap(A[i], A[r[i]]);
        for(int mid = 1; mid < limit; mid <<= 1) {
            long long Wn = fastPow(type == 1 ? G : Gi, (P - 1) / (mid << 1));
            for(int j = 0; j < limit; j += (mid << 1)) {
                long long w = 1;
                for(int k = 0; k < mid; k++, w = (w * Wn) % P) {
                    int x = A[j + k], y = w * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P,
                    A[j + k + mid] = (x - y + P) % P;
                }
            }
        }
        if(type == -1) {
            long long inv = fastPow(limit, P - 2);
            for(int i = 0; i < limit; i++) A[i] = A[i] * inv % P;
        }
    }

public:
    PolynomialMultiplier() {
        for(int i = 0; i < MAXN; i++) r[i] = 0;
        for(int i = 0; i < MAXN; i++) a[i] = 0;
        for(int i = 0; i < MAXN; i++) b[i] = 0;
    }

    vector<int> multiply(vector<int> &A, vector<int> &B) {
        N = A.size() - 1;
        M = B.size() - 1;
        copy(A.begin(), A.end(), a);
        copy(B.begin(), B.end(), b);

        while(limit <= N + M) limit <<= 1, L++;
        for(int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));

        NTT(a, 1);
        NTT(b, 1);
        for(int i = 0; i < limit; i++) a[i] = (a[i] * b[i]) % P;
        NTT(a, -1);

        vector<int> result(N + M + 1);
        for(int i = 0; i <= N + M; i++) result[i] = a[i] % P;

        return result;
    }
};
