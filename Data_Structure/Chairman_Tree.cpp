// Created by calabash_boy on 18-7-7.
// query_kth_element
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int a[maxn];int rk[maxn];int pos[maxn];
int root[maxn];int cnt,m,n,T;
struct Chairman_Tree{
    struct Node{int L,R,val;}tree[maxn*500];
    void init(){
        memset(root,0,sizeof root);
        cnt =0;
    }
    /* 建T0空树 */
    int buildT0(int l, int r){
        int k = cnt++;
        tree[k].val =0;
        if (l==r) return k;
        int mid = l+r >>1;
        tree[k].L = buildT0(l, mid);tree[k].R = buildT0(mid + 1, r);
        return k;
    }
    /* 上一个版本节点P，【ppos】+=del 返回新版本节点*/
    int update (int P,int l,int r,int ppos,int del){
        int k = cnt++;
        tree[k].val = tree[P].val +del;
        if (l==r) return k;
        int mid = l+r >>1;
        if (ppos<=mid){
            tree[k].L = update(tree[P].L,l,mid,ppos,del);
            tree[k].R = tree[P].R;
        }else{
            tree[k].L = tree[P].L;
            tree[k].R = update(tree[P].R,mid+1,r,ppos,del);
        }
        return k;
    }
    int query_kth(int lt,int rt,int l,int r,int k){
        if (l==r) return a[rk[l]];
        int mid = l+r >>1;
        if (tree[tree[rt].L].val-tree[tree[lt].L].val>=k) return query_kth(tree[lt].L,tree[rt].L,l,mid,k);
        else return query_kth(tree[lt].R,tree[rt].R,mid+1,r,k+tree[tree[lt].L].val-tree[tree[rt].L].val);
    }
}tree;
bool cmp(int x,int y){return a[x]<a[y];}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            rk[i]=i;
        }
        tree.init();
        sort(rk+1,rk+1+n,cmp);
        for (int i1=1;i1<=n;i1++){
            pos[rk[i1]] =i1;
        }
        root[0] = tree.buildT0(1, n);
        for (int i1=1;i1<=n;i1++){
            root[i1] = tree.update(root[i1-1],1,n,pos[i1],1);
        }
        while (m--){
            int l,r,k;scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",tree.query_kth(root[l-1],root[r],1,n,k));
        }
    }
    return 0;
}
