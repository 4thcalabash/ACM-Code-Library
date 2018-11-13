
// Created by calabash_boy on 18-9-14.
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000+50;
const int maxm = 20000+50;
const int INF = 0x3f3f3f3f;
int m,n,ss,tt,dis[maxn],pre[maxn];
int first[maxn],from[maxm*2],des[maxm*2],nxt[maxm*2],cost[maxm*2],flow[maxm*2],tot;
bool in[maxn];
inline void addE(int x,int y,int f,int c){
    tot++;
    from[tot] =x;des[tot] =y;
    flow[tot] =f;cost[tot] =c;
    nxt[tot] = first[x];first[x] = tot;
}
inline void addEdge(int x,int y,int f,int c){
    addE(x,y,f,c);addE(y,x,0,-c);
}
void input(){
    scanf("%d%d",&n,&m);
    tot =-1;
    memset(first,-1,sizeof first);
    for (int i=0;i<m;i++){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        addEdge(u,v,1,c);addEdge(v,u,1,c);
    }
    addEdge(0,1,2,0);
}
bool spfa(){
    memset(in,0,sizeof in);
    memset(dis,INF,sizeof dis);
    memset(pre,-1,sizeof pre);
    dis[ss] =0;in[ss] =1;
    queue<int> Q;Q.push(ss);
    while (!Q.empty()){
        int q = Q.front();
        Q.pop();in[q] = 0;
        for (int t = first[q];t!=-1;t = nxt[t]){
            int v=des[t],len=cost[t],cx=flow[t];
            if (cx&&dis[v]>dis[q]+len){
                dis[v] = dis[q]+len;
                pre[v] = t;
                if (!in[v]){
                    Q.push(v);in[v] = 1;
                }
            }
        }
    }
    return pre[tt]!=-1;
}
void solve(){
    ss =0;tt=n;
    int totflow =0,totcost =0,nowflow =0,nowcost =0;
    while (spfa()){
        nowcost =0;nowflow = INF;
        int now =pre[tt];
        while (now!=-1){
            nowflow = min(nowflow,flow[now]);
            now = pre[from[now]];
        }
        now = pre[tt];
        while (now!=-1){
            flow[now] -= nowflow;
            flow[now^1] += nowflow;
            nowcost +=cost[now];
            now = pre[from[now]];
        }
        nowcost*=nowflow;
        totflow +=nowflow;
        totcost +=nowcost;
    }
    cout<<totcost<<endl;
}
int main(){
    input();
    solve();
    return 0;
}