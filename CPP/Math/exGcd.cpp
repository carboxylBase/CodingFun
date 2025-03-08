#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
使用说明:
首先调用 init 函数初始化 ax + by = c 的参数,返回 0 表示无解.
cal 函数计算特解,通解为 X1 + k * dx , Y1 + k * dy
*/ 
class exGcd{
public:
    int a,b,dx,dy,c,gcd_ab;
    int X0,Y0,X1,Y1;
    bool init(int A,int B,int C = 0){
        a = A,b = B,c = C;
        gcd_ab = __gcd(a,b);
        if (c % gcd_ab != 0){
            return 0;
        }
        return 1;
    }
    void exgcd(int a,int b){
        if (b == 0){
            X0 = 1;
            Y0 = 0;
        }else{
            exgcd(b,a % b);
            X1 = X0,Y1 = Y0;
            X0 = Y1;
            Y0 = X1 - a / b * Y1; 
        }
        return;
    }
    void cal(){
        exgcd(a,b);
        X1 = X0 * c / gcd_ab;
        Y1 = Y0 * c / gcd_ab;
        dx = b / gcd_ab;
        dy = -a / gcd_ab; 
        return;
    }
};