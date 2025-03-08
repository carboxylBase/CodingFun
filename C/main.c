#include <stdio.h>

int n,m;

struct Node{
    int l,r,cnt;
    char val;
}nodes[2000000];
int cnt,Head;

void insert(char val){
    ++cnt;
    nodes[cnt].val = val;nodes[cnt].cnt = 0;
    nodes[cnt].l = cnt - 1;
    nodes[cnt - 1].r = cnt;
    return;
}

void query(char val){
    int cur = nodes[Head].r;

    while (nodes[cur].val != val){
        cur = nodes[cur].r;
    }

    nodes[cur].cnt++;
    while (nodes[cur].l != 0 && nodes[cur].cnt > nodes[nodes[cur].l].cnt){
        int pre = nodes[cur].l;
        // printf("%c %c\n",nodes[pre].val,nodes[cur].val);
        nodes[pre].r = nodes[cur].r;
        nodes[cur].l = nodes[pre].l;
        nodes[pre].l = cur;
        nodes[cur].r = pre;
    }

    if (nodes[cur].l == Head){
        nodes[Head].r = cur;
    }
    return;
}

void print(){
    int cur = nodes[Head].r;

    while (cur != 0){
        printf("%c ",nodes[cur].val);
        cur = nodes[cur].r;
    }

    return;
}

int main(){
    scanf("%d%d",&n,&m);

    for (int i = 1;i<n+1;i++){
        char c;
        scanf(" %c", &c); 
        insert(c);
    }

    for (int i = 1;i<m+1;i++){
        char c;
        scanf(" %c", &c); 
        query(c);
    }

    print();
    return 0;
}