#include <stdio.h>

int n,m,p;
int a[2000000],b[2000000],c[2000000],stk[2000000];
int tp;

int main(){
    scanf("%d %d %d",&n,&m,&p);
    for (int i = 1;i<n+1;i++){
        scanf("%d",&a[i]);
    }
    for (int i = 1;i<m+1;i++){
        scanf("%d",&b[i]);
    }
    for (int i = 1;i<p+1;i++){
        scanf("%d",&c[i]);
    }

    int cur = 1;
    b[0] = -100000;
    for (int i = 1;i<m+1&&cur<p+1;i++){
        if (b[i] == b[i-1]) continue;
        while (c[cur] < b[i]){
            cur++;
        }
        if (cur > p){
            break;
        }
        if (c[cur] == b[i]){
            stk[++tp] = c[cur];
        }
    }

    cur = 1;
    for (int i = 1;i<n+1;i++){
        while (stk[cur] < a[i] && cur <= tp){
            cur++;
        }

        if (cur > tp){
            if (i != n) printf("%d ",a[i]);
            else printf("%d",a[i]);
            continue;
        }

        if (stk[cur] == a[i]){

        }else{
            if (i != n) printf("%d ",a[i]);
            else printf("%d",a[i]);
        }
    }
    return 0;
}

// int main(){
//     scanf("%d %d %d",&n,&m,&p);
//     for (int i = 1;i<n+1;i++){
//         scanf("%d",&a[i]);
//     }
//     for (int i = 1;i<m+1;i++){
//         scanf("%d",&b[i]);
//     }
//     for (int i = 1;i<p+1;i++){
//         scanf("%d",&c[i]);
//     }

//     for (int i = 1;i<n+1;i++){
//         int cnt = 0;
//         for (int j = 1;j<m+1;j++){
//             if (b[j] == a[i]){
//                 cnt++;break;
//             }
//         }
//         for (int j = 1;j<p+1;j++){
//             if (c[j] == a[i]){
//                 cnt++;break;
//             }
//         }

//         if (cnt == 2){

//         }else{
//             if (i != n) printf("%d ",a[i]);
//             else printf("%d",a[i]);
//         }
//     }
// }