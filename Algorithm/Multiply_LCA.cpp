// Created by calabash_boy on 18-7-7.
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+100;
int first[maxn],des[maxn*2],nxt[maxn*2],tot;
int n,m,s;
inline int addEdge(int x,int y){
    tot++;des[tot] = y;
    nxt[tot] = first[x];
    first[x] = tot;
}
namespace Multiply_LCA{
    int fa[maxn][20],dep[maxn];
    void dfs(int u,int father){
        fa[u][0] = father;
        dep[u] = dep[father]+1;
        for (int i=1;i<20&&fa[u][i-1];i++){
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
        for (int t=first[u];t;t=nxt[t]){
            int v = des[t];
            if (v==father)continue;
            dfs(v,u);
        }
    }
    int lca(int x,int y){
        if (dep[x]<dep[y])swap(x,y);
        for (int i=19;i>=0;i--){
            if (dep[fa[x][i]]>=dep[y]){
                x = fa[x][i];
            }
        }
        if (x==y)return x;
        for (int i=19;i>=0;i--){
            if (fa[x][i]!=fa[y][i]){
                x = fa[x][i];
                y = fa[y][i];
            }
        }
        return fa[y][0];
    }
};
int main(){
    scanf("%d%d%d",&n,&m,&s);
    for (int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);addEdge(y,x);
    }
    Multiply_LCA::dfs(s,0);
    while (m--){
        int x,y;scanf("%d%d",&x,&y);
        printf("%d\n",Multiply_LCA::lca(x,y));
    }
    return 0;
}