#include<iostream>
#include<time.h>
using namespace std;
typedef long long ll;
int main()
{
    // freopen("input.txt","w",stdout);
    srand(time(0));
    cout << rand() % 10000000 + 2 << endl;
    return 0;
}

// Tree
// int main()
// {
//     // freopen("input.txt","w",stdout);
//     srand(time(0));
//     int n = rand() % 5 + 1;
//     cout << n << endl;
//     for (int i = 2;i<=n;i++){
//         cout << i << " " << rand() % (i-1) + 1 << endl;
//     }
//     return 0;
// }