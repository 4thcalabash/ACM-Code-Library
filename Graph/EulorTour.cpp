#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int maxm = 5e5 + 100;
int n,m;
int d[maxn];
//<点，到这个点走的边id>
vector<pair<int,int> > tour;
vector<pair<int,int> > E[maxn];
pair<int,int> edge[maxm];
bool used[maxm];
int now[maxn];
void dfs(int u,int e_id){
    for (; now[u] < E[u].size(); now[u] ++){
        int v,id;
        tie(v,id) = E[u][now[u]];
        if (used[id]) continue;
        used[id] = 1;
        dfs(v,id);
    }
    tour.push_back(make_pair(u,e_id));
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        edge[i] = make_pair(a,b);
        E[a].push_back(make_pair(b,i));
        E[b].push_back(make_pair(a,i));
    }
    dfs(1,-1);
    reverse(tour.begin(), tour.end());
    /*
     for (auto pr : tour){
     int u,id;
     tie(u,id) = pr;
     cerr<<u<<" "<<id<<endl;
     }
     */
    return 0;
}
