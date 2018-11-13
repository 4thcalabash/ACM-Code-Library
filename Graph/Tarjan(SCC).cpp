#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int m,n,h;int t[maxn];
int first[maxn*2],nxt[maxn*2],des[maxn*2],tot;
int dfn[maxn],low[maxn],dft;bool d[maxn];
int flag[maxn],cnt[maxn],scc;stack<int> stk;
bool in[maxn];
inline void add(int x,int y){
    tot++;des[tot] =y;
    nxt[tot] = first[x];first[x] =tot;
}
void tar(int node){
    dfn[node] = low[node] = ++dft;
    in[node] = 1;stk.push(node);
    for (int t = first[node];t;t=nxt[t]){
        int v = des[t];
        if (!dfn[v]){
            tar(v);
            low[node] = min(low[node],low[v]);
        }else if (in[v]){
            low[node] = min(low[node],dfn[v]);
        }
    }
    if (dfn[node]==low[node]){
        scc++;
        while (true){
            int temp = stk.top();
            flag[temp]=scc;
            in[temp] = 0;
            cnt[scc]++;stk.pop();
            if (temp==node)break;
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&h);
    for (int i=1;i<=n;i++){scanf("%d",t+i);}
    for (int i=0;i<m;i++){
        int u1,u2;scanf("%d%d",&u1,&u2);
        if (t[u1]==(t[u2]+1)%h)add(u2,u1);
        if (t[u2]==(t[u1]+1)%h)add(u1,u2);
    }
    for (int i=1;i<=n;i++){if (!dfn[i])tar(i);}
    for (int i=1;i<=n;i++){
        for (int t = first[i];t;t=nxt[t]){
            if (flag[i]==flag[des[t]])continue;
            else{d[flag[i]]++;}
        }
    }
    cnt[0] =n+1;int ans = 0;
    for (int i=1;i<=scc;i++){
        if (d[i]==0&&cnt[i]<cnt[ans]){ans = i;}
    }
    cout<<cnt[ans]<<endl;
    for (int i=1;i<=n;i++){
        if (flag[i]==ans){cout<<i<<" ";}
    }
    cout<<endl;
    return 0;
}