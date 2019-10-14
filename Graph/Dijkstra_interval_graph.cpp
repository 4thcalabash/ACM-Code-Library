// CF 786B
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int N = 10 * maxn;
typedef long long ll;
namespace Dijkstra{
    vector<pair<int,int> > E[N];
    ll dis[N];
    bool used[N];
    inline void add_edge(int u,int v,int w){
        E[u].push_back(make_pair(v,w));
    }
    void dijkstra(int S, int N){
        priority_queue<pair<ll,int> > pq;
        for (int i=1;i<=N;i++){
            dis[i] = 0x3f3f3f3f3f3f3f3fll;
            used[i] = 0;
        }
        dis[S] = 0;
        for (int i=1;i<=N;i++){
            pq.push(make_pair(-dis[i],i));
        }
        while (!pq.empty()){
            pair<ll,int> head = pq.top();pq.pop();
            int u; ll dist;
            tie(dist,u) = head;
            dist *= -1;
            if (used[u])continue;
            used[u] = 1;
            for (auto e : E[u]){
                int v,len;
                tie(v,len) = e;
                if (dis[v] > dist + len){
                    dis[v] = dist + len;
                    pq.push(make_pair(-dis[v],v));
                }
            }
        }
    }
    void output(int n){
        for (int i=1;i<=n;i++){
            printf("%lld ",dis[i] == 0x3f3f3f3f3f3f3f3fll ? -1:dis[i]);
        }
        puts("");
    }
}
int n,q,s;
int cnt;
struct SegmentTree{
    int id[maxn*4];
    void build(int x,int l,int r,bool up){
        id[x] = ++cnt;
        if (l == r){
            int u = id[x];
            int v = l;
            if (up)swap(u,v);
            Dijkstra::add_edge(u, v, 0);
            return;
        }
        int mid = l + r >> 1;
        build(x<<1,l,mid,up);
        build(x<<1|1,mid+1,r,up);
        int u = id[x];
        int v = id[x<<1];
        if (up)swap(u,v);
        Dijkstra::add_edge(u, v, 0);
        u = id[x];
        v = id[x<<1|1];
        if (up)swap(u,v);
        Dijkstra::add_edge(u, v, 0);
    }
    void add_edge(int x,int l,int r,int L,int R, int T, int w, bool up){
        if (l > R || L > r)return;
        if (L <= l && r <= R){
            int u = id[x];
            int v = T;
            if (up)swap(u,v);
            Dijkstra::add_edge(u, v, w);
            return;
        }
        int mid = l + r >> 1;
        add_edge(x<<1, l, mid, L, R, T, w, up);
        add_edge(x<<1|1, mid+1, r, L, R, T, w, up);
    }
}Down,Up;
int main(){
    scanf("%d%d%d",&n,&q,&s);
    cnt = n;
    Down.build(1, 1, n, false);
    Up.build(1, 1, n, true);
    while (q--){
        int t,u,l,r,w;
        scanf("%d",&t);
        if (t == 1){
            int v;
            scanf("%d%d%d",&u,&v, &w);
            l = r = v;
            t = 2;
        }else{
            scanf("%d%d%d%d",&u,&l,&r,&w);
        }
        if (t == 2){
            // u -> [l,r], len = w
            Down.add_edge(1, 1, n, l, r, u, w, true);
        }else{
            // [l,r] -> v, len = w
            Up.add_edge(1, 1, n, l, r, u, w, false);
        }
    }
    Dijkstra::dijkstra(s, cnt);
    Dijkstra::output(n);
    return 0;
}
