// Created by calabash_boy on 18-10-10.
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int first[maxn],nxt[maxn*2],from[maxn*2],des[maxn*2],isBrige[maxn*2],tot;
int dfn[maxn],low[maxn],dfs_clock;
int cnt_e[maxn],cnt_n[maxn];int bcc_cnt;
bool ok[maxn];vector <int> ans;int m,n;
inline void addEdge(int x,int y){
    tot++;
    des[tot] =y;from[tot] =x;
    nxt[tot] = first[x];first[x] = tot;
}
void input(){
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;scanf("%d%d",&u,&v);
        addEdge(u,v);addEdge(v,u);
    }
}
void dfs(int u,int fa){
    dfn[u] = low[u] = ++dfs_clock;
    for (int t = first[u];t;t=nxt[t]){
        int v = des[t];if (v==fa)continue;
        if (!dfn[v]){
            dfs(v,u);
            low[u] = min(low[v],low[u]);
            if (dfn[u]<low[v]){
                isBrige[t] = true;
                if (t&1){isBrige[t+1] = true;}
                else{isBrige[t-1] = true;}
            }
        }else if (dfn[v]<dfn[u]){low[u] = min(low[u],dfn[v]);}
    }
}
void blood_fill(int x){
    dfn[x] = bcc_cnt;
    for (int t = first[x];t;t=nxt[t]){
        if (isBrige[t])continue;
        int v = des[t];
        if (!dfn[v]){blood_fill(v);}
    }
}
void check(){
    for (int i=1;i<=n;i++){cnt_n[dfn[i]]++;}
    for (int i=1;i<=tot;i++){
        if (isBrige[i]) continue;
        cnt_e[dfn[des[i]]]++;
    }
    for (int i=1;i<=bcc_cnt;i++){
        if (cnt_n[i]*2==cnt_e[i]){ok[i]=1;}
    }
}
void output(){
    for (int i=1;i<=tot;i+=2){
        if (isBrige[i])continue;
        if (ok[dfn[des[i]]])ans.push_back((i+1)/2);
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for (int i=0;i<ans.size();i++){printf("%d ",ans[i]);}
}
void solve(){
    for (int i=1;i<=n;i++){if (!dfn[i])dfs(i,-1);}
    memset(dfn,0,sizeof dfn);
    for (int i=1;i<=n;i++){
        if (!dfn[i]){
            bcc_cnt++;
            blood_fill(i);
        }
    }
    check();output();
}
int main(){
    input();
    solve();
    return 0;
}