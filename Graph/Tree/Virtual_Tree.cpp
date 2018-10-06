//
// Created by calabash_boy on 18-10-6.
//

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 25e4+100;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int first[maxn],des[maxn*2],nxt[maxn*2],tot;
int n,m;
LL dp[maxn],leng[maxn*2], len[maxn];
int vis[maxn],dep[maxn],fa[maxn];
int sz[maxn],wson[maxn],ttop[maxn],tfa[maxn];int k,h[maxn];
int stk[maxn],top;int l[maxn],r[maxn],dfs_clock;
inline void addEdge(int x,int y,int w){
    tot++;
    des[tot] = y;leng[tot] = w;
    nxt[tot] = first[x];first[x] = tot;
}
void dfs(int u,int fath){
    l[u] = ++dfs_clock;sz[u]=1;
    for (int t = first[u];t;t=nxt[t]){
        int v = des[t];
        if (v==fath)continue;
        LL w = leng[t];
        dep[v] = dep[u] + 1;tfa[v]=u;
        len[v] = min(len[u],w);
        dfs(v,u);sz[u]+=sz[v];
        if (sz[v]>sz[wson[u]]){wson[u] = v;}
    }
    r[u]=dfs_clock ;
}
void dfs2(int u,int chain){
    ttop[u]=chain;
    if (wson[u])dfs2(wson[u],chain);
    for (int t = first[u];t;t=nxt[t]){
        int v = des[t];
        if (v==tfa[u]||v==wson[u])continue;
        dfs2(v,v);
    }
}
int lca(int x,int y){
    while (ttop[x]!=ttop[y]){
        if (dep[ttop[x]]<dep[ttop[y]])swap(x,y);
        x = tfa[ttop[x]];
    }
    if (dep[x]<dep[y])swap(x,y);
    return y;
}
bool cmp(int x,int y){return l[x]<l[y];}
void solve(){
    scanf("%d",&k);
    for (int i=0;i<k;i++){
        scanf("%d",h+i);
        vis[h[i]]=1;dp[h[i]]=0;
    }
    sort(h,h+k,cmp);
    int kk =k;
    for (int i=1;i<kk;i++){
        int temp = lca(h[i-1],h[i]);
        if (!vis[temp])vis[temp]=2,h[k++] =temp,dp[temp]=0;
    }
    if (!vis[1])vis[1]=2,h[k++]=1,dp[1]=0;
    sort(h,h+k,cmp);
    top=1;stk[0]=h[0];
    for (int i=1;i<k;i++){
        while (l[h[i]]>r[stk[top-1]])top--;
        fa[h[i]] = stk[top-1];
        stk[top++] =h[i];
    }
    for (int i=k-1;i>=0;i--){
        if (vis[h[i]]==2)dp[h[i]] = min(dp[h[i]],len[h[i]]);
        else dp[h[i]] = len[h[i]];
        dp[fa[h[i]]]+=dp[h[i]];
    }
    printf("%lld\n",dp[1]);
    for (int i=0;i<k;i++){
        vis[h[i]]=0;
    }
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);addEdge(v,u,w);
    }
    len[0] = len[1] = INF;
    dfs(1,-1);dfs2(1,1);
    scanf("%d",&m);
    while (m--){solve();}
    return 0;
}
