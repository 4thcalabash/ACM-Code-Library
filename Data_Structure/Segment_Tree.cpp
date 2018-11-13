// Created by calabash_boy on 18-9-14.
// interval modify & interval query
#include<stdio.h>
using namespace std;
const int maxn = 1e5+100;
typedef long long LL;
int a[maxn];
struct Seg_Tree{
    LL val[maxn*4];LL lazy[maxn*4];
    inline void Up(int x){val[x] = val[x<<1]+val[x<<1|1];}
    inline void Down(int x,int l,int mid,int r){
        if (lazy[x]){
            val[x<<1] += 1LL*lazy[x]*(mid-l+1);
            val[x<<1|1] += 1LL*lazy[x]*(r-mid);
            lazy[x<<1]+= lazy[x];
            lazy[x<<1|1] += lazy[x];
            lazy[x] =0;
        }
    }
    void build (int x,int l,int r){
        lazy[x] =0;
        if (l==r){val[x] = a[l];return ;}
        int mid = l+r >>1;
        build (x<<1,l,mid);build (x<<1|1,mid+1,r);
        Up(x);
    }
    void add(int x,int l,int r,int L,int R,int del){
        if (l>R||r<L)return;
        if (L<=l&&r<=R){
            val[x]+=1LL*del*(r-l+1);
            lazy[x]+=del;
            return;
        }
        int mid = l+r >>1;
        Down(x,l,mid,r);
        add(x<<1,l,mid,L,R,del);add(x<<1|1,mid+1,r,L,R,del);
        Up(x);
    }
    LL query_Sum(int x,int l,int r,int L,int R){
        if (l>R||r<L)return 0;
        if (L<=l&&r<=R)return val[x];
        int mid = l+r >>1;
        Down(x,l,mid,r);
        return query_Sum(x<<1,l,mid,L,R)+query_Sum(x<<1|1,mid+1,r,L,R);
    }
}tree;
char opt[5];int m,n;
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    tree.build(1,1,n);
    while (m--){
        int l,r,v;
        scanf("%s%d%d",opt,&l,&r);
        if (opt[0]=='Q'){
            printf("%I64d\n",tree.query_Sum(1,1,n,l,r));
        }else if (opt[0]=='C'){
            scanf("%d",&v);
            tree.add(1,1,n,l,r,v);
        }
    }
    return 0;
}
