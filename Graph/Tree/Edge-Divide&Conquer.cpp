// Created by calabash_boy on 2019/10/15.
// Luogu 5115.SAM + 边分 + 虚树DP: Given S, calculate
// \sum_{i<j and LCP(i,j)<=K1 and LCS(i,j)<=K2}{LCS(i,j) * LCP(i,j)}
// 最大度数有限制（例如parent树27度），则不需要三度化。
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
char s[maxn],t[maxn];int n,K1,K2;
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){add(*s-'a');s++;}
    }
    void add(int c){
        int p = last, np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void extract(vector<int> * E,char *s,int n,int *id,int *dep,int K){
        int temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][s[i] - 'a'];
            id[temp] = i + 1;
        }
        for (int i=2;i<=cnt;i++)E[fa[i]].push_back(i);
        for (int i=1;i<=cnt;i++){
            if (l[i] <= K)dep[i] = l[i];
            else dep[i] = 0;
        }
    }
}sam1,sam2;
vector<int> EE1[maxn * 2],E2[maxn*2];
vector<tuple<int,int,int> > E1[maxn*4];
int idd1[maxn * 2],id1[maxn*4];
int depp1[maxn * 2],dep1[maxn*4];
int id2[maxn* 2],dep2[maxn*2];
bool can_use[maxn*4];
int edge_cnt = 0;
int cnt, st[maxn * 2][20], depth[maxn * 2];
int pos2[maxn*2],pos1[maxn*4];
int dfs_clock,l[maxn*2],r[maxn*2];
void dfs2(int u,int fa){
    l[u] = ++dfs_clock;
    st[u][0] = fa;
    depth[u] = depth[fa] + 1;
    for (int i=1;i<20 && st[u][i-1];i++){
        st[u][i] = st[st[u][i-1]][i-1];
    }
    for (auto v : E2[u]){
        if (v == fa)continue;
        dfs2(v,u);
    }
    r[u] = dfs_clock;
}
int get_lca(int u,int v){
    if (depth[u] < depth[v])swap(u,v);
    for (int i=19;i>=0;i--){
        if (depth[st[u][i]] >= depth[v])u = st[u][i];
    }
    if (u == v)return u;
    for (int i=19;i>=0;i--){
        if (st[u][i] != st[v][i]){
            u = st[u][i];v = st[v][i];
        }
    }
    assert(st[u][0] == st[v][0]);
    return st[u][0];
}
//三度化
int dfs(int u,int fa){
    int now = ++cnt;
    id1[now] = idd1[u];dep1[now] = depp1[u];
    pos1[id1[now]] = now;
    int pre = now;
    for (auto v : EE1[u]){
        if (v == fa)continue;
        int temp = ++cnt;
        id1[temp] = 0;dep1[temp] = depp1[u];
        edge_cnt ++;
        E1[pre].push_back(make_tuple(temp,dep1[temp] - dep1[pre],edge_cnt));
        E1[temp].push_back(make_tuple(pre,dep1[temp] - dep1[pre],edge_cnt));
        int vid = dfs(v,u);
        edge_cnt ++;
        E1[temp].push_back(make_tuple(vid,dep1[vid] - dep1[temp],edge_cnt));
        E1[vid].push_back(make_tuple(temp,dep1[vid] - dep1[temp],edge_cnt));
        pre = temp;
    }
    return now;
}
long long ans = 0;
int sz[maxn*4];
int dis[maxn* 4];
void dfs_dis(int u,int fa,int len){
    dis[u] = len;
    for (auto e : E1[u]){
        int v,lll,edge_id;tie(v,lll,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_dis(v,u,len + lll);
    }
}
void dfs_sz(int u,int fa){
    sz[u] = 1;
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_sz(v,u);
        sz[u] += sz[v];
    }
}
void dfs_edge(int u,int fa,int &e_id,int &uu,int &vv,int &ww,int &max_sz,int tot_node){
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        int max_sz_t = max(sz[v],tot_node - sz[v]);
        if (max_sz_t < max_sz){
            max_sz = max_sz_t;
            uu = u;vv = v;ww = len;e_id = edge_id;
        }
        dfs_edge(v,u,e_id,uu,vv,ww,max_sz,tot_node);
    }
}
void dfs_node(int u,int fa,vector<int> &nodes){
    if (id1[u])nodes.push_back(id1[u]);
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_node(v,u,nodes);
    }
}
int color[maxn * 2];
int vis[maxn];
long long dp[maxn * 2];
long long dp_cnt[maxn*2][2];
long long dp_sum[maxn*2][2];
int stk[maxn*2];
int fa[maxn*2];
inline void clear(int x,int type){
    dp[x] = 0;vis[x] = type;
    for (int c = 0; c < 2;c ++)dp_cnt[x][c] = dp_sum[x][c] = 0;
}
void DP(vector<int> & nodes_,int ww){
    vector<int> nodes(0);
    for (int x : nodes_){
        nodes.push_back(pos2[x]);
    }
    for (int x : nodes)clear(x,1);
    sort(nodes.begin(),nodes.end(),[](int x,int y){
        return l[x] < l[y];
    });
    int SZ = nodes.size();
    for (int i=1;i<SZ;i ++){
        int temp = get_lca(nodes[i-1],nodes[i]);
        if (!vis[temp]){
            nodes.push_back(temp);
            clear(temp,2);
        }
    }
    if (!vis[1]){
        nodes.push_back(1);
        clear(1,2);
    }
    sort(nodes.begin(),nodes.end(),[](int x,int y){
        return l[x] < l[y];
    });
    int top = 1;
    stk[0] = nodes[0];
    for (int i=1;i<nodes.size();i++){
        while (l[nodes[i]] > r[stk[top-1]]) top --;
        fa[nodes[i]] = stk[top-1];
        stk[top++] = nodes[i];
    }
    long long anss = 0;
    for (int i= nodes.size() - 1;i >=0 ;i --){
        int u = nodes[i], c = vis[u] == 1? color[id2[u]] - 1: -1;
        if (c != -1){
            long long A = dep1[pos1[id2[u]]] - dis[pos1[id2[u]]];
            dp[u] += A * dp_cnt[u][!c] + dp_sum[u][!c];
            dp[u] -= dp_cnt[u][!c] * ww;
            dp_cnt[u][c] ++;
            dp_sum[u][c] += A;
        }
        long long temp_ans = dp[u] * dep2[u];
        assert(temp_ans %2 == 0);
        anss += temp_ans/2;
        dp[fa[u]] += dp_cnt[fa[u]][0] * dp_sum[u][1] + dp_cnt[u][0] * dp_sum[fa[u]][1];
        dp[fa[u]] += dp_cnt[fa[u]][1] * dp_sum[u][0] + dp_cnt[u][1] * dp_sum[fa[u]][0];
        dp[fa[u]] -= (dp_cnt[fa[u]][1] * dp_cnt[u][0] + dp_cnt[fa[u]][0] * dp_cnt[u][1]) * ww;
        for (int c = 0;c < 2;c ++){
            dp_cnt[fa[u]][c] += dp_cnt[u][c];
            dp_sum[fa[u]][c] += dp_sum[u][c];
        }
    }
    ans += anss;
    for (int x : nodes)vis[x] = 0;
}
void calc(int uu,int vv,int ww){
    vector<int> L(0),R(0),nodes(0);
    dfs_node(uu,0,L);dfs_node(vv,0,R);
    for (int x : L){color[x] = 1;nodes.push_back(x);}
    for (int x : R){color[x] = 2;nodes.push_back(x);}
    DP(nodes,ww);
}
void dfs(int root){
    dfs_sz(root,0);
    int tot_node = sz[root];
    if (tot_node == 1)return;
    int edge_id,uu,vv,ww,max_sz = tot_node + 1;
    dfs_edge(root,0,edge_id,uu,vv,ww,max_sz,tot_node);
    can_use[edge_id] = false;
    dfs_dis(uu,0,0);dfs_dis(vv,0,0);
    calc(uu,vv,ww);dfs(uu);dfs(vv);
}
int main(){
    scanf("%s%d%d",s,&K1,&K2);
    n = strlen(s);
    memcpy(t,s,sizeof s);reverse(t,t + n);
    sam1.init(s);sam2.init(t);
    sam1.extract(EE1,s,n,idd1,depp1,K2);
    sam2.extract(E2,t,n,id2,dep2,K1);
    for (int i=1;i<= sam2.cnt; i ++){
        if (id2[i]){
            id2[i] = n + 1 - id2[i];
            pos2[id2[i]] = i;
        }
    }
    int root1 = dfs(1,0);int root2 = 1;
    dfs2(root2,0);
    memset(can_use,true,sizeof can_use);
    dfs(root1);
    cout<<ans<<endl;
    return 0;
}