//
// Created by calabash_boy on 18-10-25.
//
#include<bits/stdc++.h>
#define maxn 1300
#define maxm 120010
using namespace std;
struct edge{
    int u,v,cap;
}e[maxm];
struct Dinic{
    int tp,s,t,dis[maxn],cur[maxn],que[maxn];
    vector<edge>e;vector<int>v[maxn];
    void AddEdge(int x,int y,int flw){
        e.push_back(edge{x,y,flw});
        e.push_back(edge{y,x,0});
        v[x].push_back(e.size()-2);
        //v[y].push_back(e.size()-1);
    }
    int bfs(){
        memset(dis,0x3f,sizeof dis);
        int l=1,r=1;que[1]=s;dis[s]=0;
        while(l<=r){
            int p=que[l++],to;
            for(int i:v[p])if(e[i].cap && dis[to=e[i].v]>1e9)
                    dis[to]=dis[p]+1,que[++r]=to;
        }
        return dis[t]<1e9;
    }
    int dfs(int p,int a){
        if(p==t || !a)return a;
        int sf=0,flw;
        for(int &i=cur[p],to;i<(int)v[p].size();++i){
            edge &E=e[v[p][i]];
            if(dis[to=E.v]==dis[p]+1 && (flw=dfs(to,min(a,E.cap)))){
                E.cap-=flw;e[v[p][i]^1].cap+=flw;
                a-=flw;sf+=flw;
                if(!a)break;
            }
        }
        return sf;
    }
    int dinic(int s,int t,int tp=1){
        this->s=s;this->t=t;this->tp=tp;
        int flw=0;
        while(bfs()){
            memset(cur,0,sizeof cur);
            flw+=dfs(s,INT_MAX);
        }
        return flw;
    }
}sol;
int n,m,i,s,t,ans;
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(i=0;i<m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].cap);
    sort(e,e+m,[](edge a,edge b){return a.cap>b.cap;});
    for(int tp:{0,1})for(int p=1<<30,i=0;p;p/=2){
            while(i<m && e[i].cap>=p){
                if(tp)sol.v[e[i].v].push_back(i*2+1);
                else sol.AddEdge(e[i].u,e[i].v,e[i].cap);
                i++;
            }
            ans+=sol.dinic(s,t,tp);
        }
    printf("%d\n",ans);
    return 0;
}
