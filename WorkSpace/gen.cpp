#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int _ = 5;
    cout<<_<<endl;
    while (_--){
 int n = rand()%5+1;
    int m = rand()%10+1;
    cout<<n<<" "<<m<<endl;
    for (int i = 1;i<=n;i++){
        cout<<rand()%6+1<<" ";
    }
    cout<<endl;
    int x= 1;
    int t = rand()%n+1;
    cout<<x<<" "<<t<<endl;
    for (int i = 1;i<m;i++){
        x += rand()%5+1;
        cout<<x<<" "<<rand()%n+1<<endl;
    }
    }
   
    return 0;
}