//
// Created by calabash_boy on 18-10-6.
//
//求树上长度小于等于k的有向路径数
#include<stdio.h>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAX = 1e4+100;
const int INF = 0x3f3f3f3f;
int first [MAX*2];  int des[MAX*2];
int len[MAX*2];  int nxt[MAX*2];
int n,k,tot;  int a[MAX];  int sum[MAX];
int dp[MAX];  int dis[MAX];  int num,ans;
bool vis[MAX];  int Sum,Min,Minid;
void init(){
    memset(first,0,sizeof first);
    tot =0;  ans =0;
    memset(vis,0,sizeof vis);
}
inline void add(int x,int y,int z){
    tot++;
    des[tot]= y;  len[tot] =z;
    nxt[tot] = first[x];  first[x] = tot;
}
void input(){
    for (int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);  add(v,u,w);
    }
}
void dfs1(int node,int father){
    sum[node] = 1;  dp[node] = 0;
    for (int t = first[node];t;t = nxt[t]){
        int v = des[t];
        if (v == father||vis[v]){
            continue;
        }
        dfs1(v,node);
        sum[node] += sum[v];
        dp[node] = max(dp[node],sum[v]);
    }
}
void dfs2(int node,int father){
    int temp = max(dp[node],Sum-sum[node]);
    if (temp<Min){
        Min = temp;  Minid = node;
    }
    for (int t = first[node];t;t = nxt[t]){
        int v = des[t];
        if (v==father||vis[v]){  continue;  }
        dfs2(v,node);
    }
}
int getRoot(int u){
    dfs1(u,0);  Sum = sum[u];
    Min = INF;  Minid = -1;
    dfs2(u,0);
    return Minid;
}
void getDist(int node,int father,int dist){
    dis[num++] = dist;
    for (int t = first[node];t;t = nxt[t]){
        int v =des[t];
        if (v == father||vis[v]){  continue;  }
        getDist(v,node,dist+len[t]);
    }
}
int calc (int u,int val){
    num=0;  int res =0;
    getDist(u,0,0);
    sort(dis,dis+num);
    int i=0;int j=num-1;
    while (i<j){
        if (dis[i]+dis[j]+2*val<=k){
            res+=j-i;
            i++;
        }else{  j--;  }
    }
    return res;
}
void solve(int u){
    int root = getRoot(u);
    ans +=calc(root,0);  vis[root] = true;
    for (int t = first[root];t;t = nxt[t]){
        int v = des[t];
        if (vis[v]){
            continue;
        }
        ans-=calc(v,len[t]);
        solve(v);
    }
}
int main(){
    while (scanf("%d%d",&n,&k)!=EOF&&n&&k){
        init();
        input();
        solve(1);
        printf("%d\n",ans);
    }
    return 0;
}