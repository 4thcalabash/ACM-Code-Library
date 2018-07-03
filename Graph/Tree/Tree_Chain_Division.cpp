//
// Created by calabash_boy on 18-7-3.
//统计路径上标记边的个数
#include<bits/stdc++.h>
using namespace std;
const int maxn = 250000+100;
int first[maxn*2];int nxt[maxn*2];int des[maxn*2];
int tpos[maxn];int dep[maxn];int top[maxn];
int fa[maxn]; int wson[maxn];  int sz[maxn];
int n,q,tot=0,cnt=0;  char s[10];
struct BIT{
    int sm[maxn];
    int lowbit(int _x){return _x&(-_x);}
    void build (int l,int r){
        for (int i=l;i<=r;i++){
            add(i,1);
        }
    }
    void add(int x,int val){
        while (x<=maxn){
            sm[x]+=val;
            x+=lowbit(x);
        }
    }
    int sum(int x){
        int res =0;
        while (x){
            res+=sm[x];
            x-=lowbit(x);
        }
        return res;
    }
    int query_sum(int l,int r){
        return sum(r)-sum(l-1);
    }
    void modify(int u,int v){
        if (fa[u]!=v){  swap(u,v);  }
        add(tpos[u],-1);
    }
    int get_sum(int u,int v){
        int res =0;
        while (top[u]!=top[v]){
            if (dep[top[u]]<dep[top[v]]){  swap(u,v);  }
            res+= query_sum(tpos[top[u]],tpos[u]);
            u = fa[top[u]];
        }
        if (dep[u]<dep[v]){  swap(u,v); }
        res += query_sum(tpos[v],tpos[u]);
        return res;
    }
}tree;

inline void addEdge(int _u, int _v){
    des[++tot] = _v;
    nxt[tot] = first[_u];
    first[_u] = tot;
}
//统计dep，子树sz，重儿子wson
void dfs(int node,int father){
    dep[node] = dep[father]+1;
    fa[node] = father;  sz[node] =1;
    for (int t = first[node];t;t = nxt[t]){
        int v = des[t];
        if (v==father){  continue;  }
        dfs(v,node);
        if (sz[v]>sz[wson[node]]){
            wson[node] = v;
        }
        sz[node]+=sz[v];
    }
}
//node所在链的头是chain
void dfs2(int node,int father,int chain){
    top[node] = chain;  tpos[node] = ++cnt;
    if (wson[node]){
        dfs2(wson[node],node,chain);
    }
    for (int t = first[node];t;t = nxt[t]){
        int v = des[t];
        if (v==father||v ==wson[node]){  continue;  }
        dfs2(v,node,v);
    }
}

int main(){
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        int u,v;  scanf("%d%d",&u,&v);
        addEdge(u, v);addEdge(v, u);
    }
    //链剖
    dfs(1,0);
    dfs2(1, 0, 1);
    //维护
    tree.build(2,n);
    scanf("%d",&q);
    q+=n-1;
    while (q--){
        scanf("%s",s);
        if (s[0]=='W'){
            int x;
            scanf("%d",&x);
            printf("%d\n",tree.get_sum(1,x));
        }else{
            int x,y;
            scanf("%d%d",&x,&y);
            tree.modify(x,y);
        }
    }
    return 0;
}
