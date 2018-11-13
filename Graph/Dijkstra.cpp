//
// Created by calabash_boy on 18-11-13.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const int maxn = 100005;
vector<pair<int,int> > E[maxn];
int n,m,k;
namespace Dijkstra{
    ll dis[maxn];
    bool used[maxn];
    vector<pair<int,int> > *Edge;
    int S;
    int N;
    struct Node{
        int x;ll dis;
        bool operator < (const Node &other)const{
            return other.dis < dis;
        }
    };
    void init(vector<pair<int,int> >*Edgee,int n,int st){
        Edge = Edgee;
        S =st;
        N = n;
    }
    void work(){
        memset(dis,inf,sizeof dis);
        memset(used,0,sizeof used);
        dis[S] = 0;
        priority_queue<Node> pq;
        pq.push({S,0});
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
};
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<m;i++){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        E[x].push_back({y,w});
    }
    Dijkstra::init(E,n,k);
    Dijkstra::work();
    for (int i=1;i<=n;i++){
        printf("%lld ",Dijkstra::dis[i]);
    }
    puts("");
    return 0;
}
