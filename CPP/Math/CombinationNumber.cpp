#include <bits/stdc++.h>
typedef long long ll;
const ll MOD = 1000000007;
const ll MAXN = 10001000;
class CombinationNumber{
public:
    ll fact[MAXN];    
    ll inv[MAXN];
    ll quick(ll base, ll k) {
        ll res = 1;
        while (k) {
            if (k & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            k >>= 1;
        }
        return res;
    }     

    void precompute() {
        fact[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        inv[MAXN - 1] = quick(fact[MAXN - 1], MOD - 2); 
        for (int i = MAXN - 2; i >= 0; i--) {
            inv[i] = inv[i + 1] * (i + 1) % MOD; 
        }
    }   

    ll C(ll n, ll m) {
        if (m > n || m < 0) {
            return 0;
        }
        return fact[n] * inv[m] % MOD * inv[n - m] % MOD; 
    } 

    void init(){
        precompute();
    }
};