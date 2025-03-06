#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;

class Primes{
public:
    ll notPrime[N];
    vector<ll> primes;
    void sieve(int maxn){
        for (ll i = 2;i<maxn + 1;i++){
            if (!notPrime[i]){
                primes.push_back(i);
                for (int j = i*2;j<maxn + 1;j+=i){
                    notPrime[j] = 1;
                }
            }
        }
        return;
    }
};