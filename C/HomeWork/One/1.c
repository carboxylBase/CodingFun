#include <stdio.h>

struct Node{
    int l,r,val;
}nodes[2000000];

// 头节点索引固定为 0
int Head = 0,cnt = 0;

// 插入节点
void insert(int val){
    ++cnt;
    nodes[cnt].val = val;
    if (nodes[Head].r == 0){
        nodes[Head].r = cnt;
        nodes[cnt].l = Head;
    }else{
        int cur = nodes[Head].r;
        while (1){
            if (nodes[cur].val >= val){
                nodes[nodes[cur].l].r = cnt;
                nodes[cnt].l = nodes[cur].l;
                nodes[cnt].r = cur;
                nodes[cur].l = cnt;
                return;
            }else{
                if (nodes[cur].r == 0) break;
                cur = nodes[cur].r;
            }
        }

        nodes[cur].r = cnt;
        nodes[cnt].l = cur;
        nodes[cnt].r = 0;
    }

    return;
}

// 删除节点,待编写
void delete(int val){
    return;
}

// 遍历表
void print(){
    int cur = nodes[Head].r;

    while (cur != 0){
        printf("%d ",nodes[cur].val);
        cur = nodes[cur].r;
    }

    return;
}

int main(){
    int n;
    scanf("%d",&n);

    for (int i = 0;i<n+1;i++){
        int val;
        scanf("%d",&val);
        insert(val);
    }

    print();

    return 0;
}