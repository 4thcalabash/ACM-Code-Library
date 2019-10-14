// Created by calabash_boy on 2019/10/14.
#include<bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
const int inf = 1e9 + 5;
const int maxn = 80000 + 50;
const int maxq = 160000 + 50;
struct Node{
    int lson,rson,k,b;
    //y = k * x + b
    void init(){
        lson = rson = 0;
        k = b = inf;
    }
}nodes[maxn * 300];
int node_cnt = 0;
int root[maxn];
int update(int x,int l,int r,int L,int R,int k,int b){
    int now = node_cnt ++;
    nodes[now] = nodes[x];
    int mid = l + r >> 1;
    if (l == L && r == R){
        if (k * mid + b < nodes[now].k * mid + nodes[now].b){
            swap(k,nodes[now].k);
            swap(b,nodes[now].b);
        }
        if (l == r)return now;
        if (k * l + b < nodes[now].k * l + nodes[now].b){
            nodes[now].lson = update(nodes[x].lson,l,mid,l,mid,k,b);
        }
        if (k * r + b < nodes[now].k * r + nodes[now].b){
            nodes[now].rson = update(nodes[x].rson,mid+1,r,mid+1,r,k,b);
        }
        return now;
    }
    if (L <= mid)nodes[now].lson = update(nodes[x].lson,l,mid,L,min(mid,R),k,b);
    if (mid + 1 <= R)nodes[now].rson = update(nodes[x].rson,mid+1,r,max(mid+1,L),R,k,b);
    return now;
}
int n,q;
int a[maxn], b[maxn], c[maxn];
vector<int> E[maxn];
void dfs(int u,int fa){
    root[u] = update(root[fa],0,inf,0,c[u],b[u],a[u]);
    for (int v : E[u]){
        if (v == fa)continue;
        dfs(v,u);
    }
}
ll query(int x,int l,int r,int pos){
    int res = nodes[x].k * pos + nodes[x].b;
    //cerr<<x<<" "<<l<<" "<<r<<":"<<nodes[x].k<<" "<<nodes[x].b<<":"<<pos<<" "<<res<<endl;
    if (l == r)return res;
    int mid = l + r >> 1;
    if (pos <= mid && nodes[x].lson )res = min(res,query(nodes[x].lson,l,mid,pos));
    else if (pos > mid &&nodes[x].rson ) res = min(res,query(nodes[x].rson,mid+1,r,pos));
    return res;
}
signed main(){
    scanf("%lld%lld",&n,&q);
    for (int i=1;i<=n;i++)scanf("%lld",a+i);
    for (int i=1;i<=n;i++)scanf("%lld",b+i);
    for (int i=1;i<=n;i++)scanf("%lld",c+i);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    root[0] = 0;node_cnt ++;nodes[0].init();
    dfs(1,0);
    while (q--){
        int v,t;
        scanf("%lld%lld",&v,&t);
        printf("%lld\n",query(root[v],0,inf,t));
    }
    return 0;
}