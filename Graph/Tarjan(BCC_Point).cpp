// Created by calabash_boy on 18-10-10.
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int first[maxn],des[maxn*2],nxt[maxn*2],tot;
int bcc_cnt,cnt_n[maxn],cnt_e[maxn],bcc_no[maxn];
int dfn[maxn],low[maxn],dfs_clock;
int st[maxn*2],top;bool ok[maxn];
vector<int> ans;vector<int> temp;
int m,n;
inline void addEdge(int x,int y){
    tot++;des[tot] = y;
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
        int v = des[t];
        if (v==fa)continue;
        if (!dfn[v]){
            st[top++] = t;dfs(v,u);
            low[u] = min(low[u],low[v]);
            if (low[v]>=dfn[u]){
                bcc_cnt++;ok[bcc_cnt] = true;
                temp.clear();
                while (true){
                    int tt = st[--top];
                    temp.push_back((tt+1)/2);
                    if (bcc_no[des[tt]]!=bcc_cnt){
                        bcc_no[des[tt]] = bcc_cnt;
                        cnt_n[bcc_cnt]++;
                    }else{
                        ok[bcc_cnt] = false;
                    }
                    cnt_e[bcc_cnt]++;
                    if (tt==t)break;
                }
                if (ok[bcc_cnt]&&temp.size()>1){
                    for (int i=0;i<temp.size();i++){
                        ans.push_back(temp[i]);
                    }
                }
            }
        }else if (dfn[v]<dfn[u]){
            st[top++] = t;
            low[u] = min(low[u],dfn[v]);
        }
    }
}
void solve(){
    for (int i=1;i<=n;i++){if (!dfn[i])dfs(i,-1);}
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for (int i=0;i<ans.size();i++){printf("%d ",ans[i]);}
}
int main(){
    input();
    solve();
    return 0;
}