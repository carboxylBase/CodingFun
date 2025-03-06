#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class RandomNumberGenerator{
public:
    RandomNumberGenerator() : gen(std::random_device{}()){}

    ll generate(ll l,ll r){
        uniform_int_distribution<> dis(l,r);
        return dis(gen);
    }
private:
    mt19937 gen;
};