//
// Created by calabash_boy on 18-9-14.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int INF = 0x3f3f3f3f;
int first[maxn],nxt[maxn*2],des[maxn*2],c[maxn*2],tot;
int dep[maxn];int m,n,ss,tt;
void init(){
    memset(first,-1,sizeof first);
    tot =-1;
}
inline void addEdge(int u,int v,int w){
    tot++;
    des[tot] = v;c[tot] =w;
    nxt[tot] = first[u];first[u] = tot;
}
void input(){
    for (int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);addEdge(v,u,0);
    }
}
bool bfs(){
    memset(dep,-1,sizeof dep);
    dep[ss] =0;
    queue<int> Q;Q.push(ss);
    while (!Q.empty()){
        int q = Q.front();Q.pop();
        for (int t = first[q];t!=-1;t= nxt[t]){
            int v = des[t],cx = c[t];
            if (dep[v]==-1&&cx){
                dep[v] = dep[q]+1;
                Q.push(v);
            }
        }
    }
    return dep[tt]!=-1;
}
int dfs(int node,int now){
    if (node==tt)return now;
    int res =0;
    for (int t = first[node];t!=-1&&res<now;t=nxt[t]){
        int v = des[t],cx = c[t];
        if (dep[v]==dep[node]+1&&cx){
            int x = min(cx,now-res);
            x = dfs(v,x);
            res +=x;
            c[t] -= x;c[t^1]+=x;
        }
    }
    if (!res) dep[node] = -2;
    return res;
}
void solve(){
    int res =0,del =0;
    ss =1;tt =n;
    while (bfs()){
        while (del = dfs(ss,INF)){res +=del;}
    }
    cout<<res<<endl;
}
int main(){
    while (scanf("%d%d",&m,&n)!=EOF){
        init();
        input();
        solve();
    }
    return 0;
}
