// Created by calabash_boy on 18-9-14.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 11000;
const int maxm = 110000;
const int INF = 0x3f3f3f3f;
struct Max_Flow{
    int first[maxn],nxt[maxm*2],des[maxm*2],c[maxm*2],tot;
    int dep[maxn];int ss,tt;
    Max_Flow(){ clear(); }
    void clear(){
        memset(first,-1,sizeof first);tot =-1;
    }
    inline void addEdge(int u,int v,int w){
        tot++;
        des[tot] = v;c[tot] =w;
        nxt[tot] = first[u];first[u] = tot;
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
                res+=x;c[t]-=x;c[t^1]+=x;
            }
        }
        if (!res) dep[node] = -2;
        return res;
    }
    // tuple<from,to,flow>
    void init(vector<tuple<int,int,int> > Edge){
        for (auto tp : Edge){
            int u,v,w;tie(u,v,w) = tp;
            addEdge(u,v,w);addEdge(v,u,0);
        }
    }
    // s->t max_flow
    ll max_flow(int s,int t){
        ss = s;tt = t;
        ll res =0,del =0;
        while (bfs()){while (del = dfs(ss,INF)){res += del;}}
        return res;
    }
}net;
int n,m,s,t;
vector<tuple<int,int,int> > E;
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        E.push_back(make_tuple(u,v,w));
    }
    net.init(E);
    printf("%lld\n",net.max_flow(s,t));
    return 0;
}