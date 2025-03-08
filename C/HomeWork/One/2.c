#include <stdio.h>

int a[2000000];

struct Node{
    int nxt,val;
}nodes[2000000];

int cnt = 0,Head = 0;

void insert(int val){
    nodes[cnt + 1].nxt = cnt;
    nodes[++cnt].val = val;
    return;
}

int main(){
    int n;
    scanf("%d",&n);

    for (int i = 1;i<n+1;i++){
        scanf("%d",&a[i]);
        insert(a[i]);
    }

    for (int i = n;i>0;i--){
        if (i != 1) printf("%d ",a[i]);
        else printf("%d",a[i]);
    }
    printf("\n");

    int cur = cnt;
    while (cur != 0){
        if (nodes[cur].nxt != 0) printf("%d ",nodes[cur].val);
        else printf("%d",nodes[cur].val);
        cur = nodes[cur].nxt;
    }
    return 0;
}

// 评测有问题,为什么把最后一个空格也读进去了...