/* Created by calabash_boy on 19-12-4.
 * tutorial:
 *https://codeforces.com/blog/entry/62331?tdsourcetag=s_pctim_aiomsg
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
/* 维护最后出现位置在i（左端点）的本质不同串数量 */
struct SegmentTree_Sum{
    ll Sum[maxn * 8],Lazy[maxn*8];
    void down(int x,int l,int mid,int r){
        Sum[x<<1] += Lazy[x] * (mid - l + 1);
        Sum[x<<1|1] += Lazy[x] * (r - mid);
        Lazy[x<<1] += Lazy[x];
        Lazy[x<<1|1] += Lazy[x];
        Lazy[x] = 0;
    }
    void up(int x){Sum[x] = Sum[x<<1] + Sum[x<<1|1];}
    void update(int x,int l,int r,int L,int R,int val){
        if (l > R or L > r)return;
        if (L <= l and r <= R){
            Sum[x] += 1ll * val * (r - l + 1);
            Lazy[x] += val;
            return;
        }
        int mid = l + r >> 1;down(x,l,mid,r);
        update(x<<1,l,mid,L,R,val);update(x<<1|1,mid+1,r,L,R,val);
        up(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if (l > R or L > r)return 0;
        if (L <= l and r <= R)return Sum[x];
        int mid = l + r >> 1;down(x,l,mid,r);
        return query(x<<1,l,mid,L,R) + query(x<<1|1,mid+1,r,L,R);
    }
}segtree;
struct SegmentTree_Max{
    int Max[maxn*8];
    void update(int x,int l,int r,int pos,int val){
        Max[x] = max(Max[x],val);
        if (l == r)return;
        int mid = l + r >> 1;
        if (pos <= mid)update(x<<1,l,mid,pos,val);
        else update(x<<1|1,mid+1,r,pos,val);
    }
    int query(int x,int l,int r,int L,int R){
        if (l > R or L > r)return -1;
        if (L <= l and r <= R)return Max[x];
        int mid = l + r >> 1;
        return max(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
}dfstree;
int n,q;
char s[maxn];
ll ans[maxn];
typedef pair<pair<int,int>,int> Query;
vector<Query> query;
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    /* 每个color最上边一个点 */
    int up_to[maxn];
    /* 是否被染过色 */
    bool used[maxn*2];
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){add(*s-'a');s++;}
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
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
    vector<int> E[maxn * 2];
    int in[maxn*2],out[maxn*2],dfn;
    void dfs(int u){
        in[u] = ++dfn;
        for (int v:E[u])dfs(v);
        out[u] = dfn;
    }
    void gao(){
        for (int i=2;i<=cnt;i++)E[fa[i]].push_back(i);
        dfs(1);
        for (int i=1,now = 1;i<=n;i++){
            now = nxt[now][s[i] - 'a'];
            assert(l[now] == i);
            segtree.update(1,1,n,1,i,1);
            int u = now;
            while (u != 1 and !used[u]){
                used[u] = true;
                u = fa[u];
            }
            while (u != 1){
                int cur = dfstree.query(1,1,cnt,in[u],out[u]);
                segtree.update(1,1,n,cur - l[u]+1,cur - l[up_to[cur]],-1);
                swap(up_to[cur],u);
            }
            dfstree.update(1,1,cnt,in[now],i);
            up_to[i] = 1;
            while (!query.empty() and query.back().first.second == i){
                int l = query.back().first.first;
                int id = query.back().second;
                ans[id] = segtree.query(1,1,n,l,i);
                query.pop_back();
            }
        }
    }
}sam;
int main(){
    cin>>n>>q;
    cin>>s+1;
    sam.init(s+1);
    for (int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        query.push_back({{l+1,r+1},i});
    }
    sort(query.begin(),query.end(),[](Query x,Query y){
        return x.first.second > y.first.second;
    });
    sam.gao();
    for (int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}