// Created by calabash_boy on 18-11-13.
// remain k bi-edge such that the most points' dis == min_dis
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf_ll = 0x3f3f3f3f3f3f3f3fll;
const int inf = 0x3f3f3f3f;
const int maxn = 300005;
struct EDGE{int first,second,third;};
int n,m,k;
namespace Short_Path_Tree{
    vector<pair<int,int> > Edge[maxn];
    bool used[maxn];
    void add_edge(int x,int y,int w) {Edge[x].push_back({y,w});}
    void output(const vector<int> &ans){
        printf("%d\n",(int) ans.size());
        for (int v : ans)printf("%d ",v);
        puts("");exit(0);
    }
    void solve(int K){
        vector<int> ans(0);queue<int> Q;
        used[1] = 1;Q.push(1);
        while (!Q.empty()){
            if (ans.size()== K)output(ans);
            int head = Q.front();Q.pop();
            for (auto pr : Edge[head]){
                if (used[pr.first])continue;
                used[pr.first] = 1;
                ans.push_back(pr.second);
                Q.push(pr.first);
                if (ans.size()==K)output(ans);
            }
        }
        output(ans);
    }
};
namespace Dijkstra{
    ll dis[maxn];bool used[maxn];
    vector<EDGE > *Edge;int S,N;
    struct Node{
        int x;ll dis;
        bool operator < (const Node &other)const{
            return other.dis < dis;
        }
    };
    void init(vector<EDGE>*Edgee,int n,int st){
        Edge = Edgee;S =st;N = n;
    }
    void work(){
        memset(dis,inf,sizeof dis);
        priority_queue<Node> pq;
        dis[S] = 0;pq.push({S,0});
        while (!pq.empty()){
            Node head = pq.top();pq.pop();
            if (used[head.x])continue;
            used[head.x] = 1;
            for (auto pr : Edge[head.x]){
                if (dis[pr.first] > dis[head.x] + pr.second){
                    dis[pr.first] = dis[head.x] + pr.second;
                    pq.push({pr.first,dis[pr.first]});
                }
            }
        }
    }
    void extract_spt(){
        for (int u=1;u<=N;u++){
            for (auto pr : Edge[u]){
                if (dis[pr.first] == dis[u] + pr.second){
                    Short_Path_Tree::add_edge(u,pr.first,pr.third);
                }
            }
        }
    }
};
vector<EDGE> E[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=m;i++){
        int x,y,w;scanf("%d%d%d",&x,&y,&w);
        E[x].push_back({y,w,i});
        E[y].push_back({x,w,i});
    }
    Dijkstra::init(E,n,1);
    Dijkstra::work();
    Dijkstra::extract_spt();
    Short_Path_Tree::solve(k);
    return 0;
}