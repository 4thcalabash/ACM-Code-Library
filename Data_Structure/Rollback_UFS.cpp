//加边删边二部图判定。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
struct UFS{
    int fa[maxn];
    int sz[maxn];
    int len[maxn];
    stack<pair<int*,int> > stk;
    void init(){
        for (int i=1;i<maxn;i++){
            fa[i] = i;
            sz[i] = 1;
            len[i] = 0;
        }
    }
    UFS(){
        init();
    }
    pair<int,int> find(int x){
        if (fa[x] == x)return make_pair(x,0);
        else{
            pair<int,int> ret = find(fa[x]);
            ret.second ^= len[x];
            return ret;
        }
    }
    // 0 fail
    // 1 succ but not update
    // 2 succ and update
    int merge(int x,int y){
        int fx,lenx;
        int fy,leny;
        tie(fx,lenx) = find(x);
        tie(fy,leny) = find(y);
        if (fx == fy){
            return lenx ^ leny;
        }
        if (sz[fx] > sz[fy]){
            swap(lenx,leny);
            swap(x,y);
            swap(fx,fy);
        }
        stk.push(make_pair(&sz[fy],sz[fy]));
        stk.push(make_pair(&fa[fx],fa[fx]));
        fa[fx] = fy;
        sz[fy] += sz[fx];
        if (lenx == leny){
            len[fx] = 1;
        }else{
            len[fx] = 0;
        }
        return 2;
    }
    void rollback(){
        for (int i=0;i<2;i++){
            int * tar;
            int val;
            tie(tar,val) = stk.top();
            stk.pop();
            (*tar) = val;
        }
        
    }
}ufs;
const char* YES = "YES";
const char* NO = "NO";
bool ans[maxn];
struct SegmentTree{
    vector<pair<int,int> > edges[maxn*4];
    void put(int x,int l,int r,int L,int R,pair<int,int> e){
        if (l > R || L > r)return;
        if (L <= l && r <= R){
            edges[x].push_back(e);
            return;
        }
        int mid = l + r >> 1;
        put(x<<1,l,mid,L,R,e);
        put(x<<1|1,mid+1,r,L,R,e);
    }
    void dfs(int x,int l,int r){
        int succ = true;
        int cnt = 0;
        for (auto e : edges[x]){
            int x,y;
            tie(x,y) = e;
            int ret = ufs.merge(x, y);
            succ &= ret!= 0;
            if (!succ){
                for (int i=0;i<cnt;i++)
                    ufs.rollback();
                return;
            }
            cnt += ret == 2;
        }
        if (l == r){
            ans[l] = succ;
            for (int i=0;i<cnt;i++)
                ufs.rollback();
            return;
        }
        int mid = l + r >> 1;
        dfs(x<<1,l,mid);
        dfs(x<<1|1,mid+1,r);
        for (int i=0;i<cnt;i++)
            ufs.rollback();
    }
    void debug(int x,int l,int r){
        cerr<<x<<" : "<<"[ "<<l<<" , "<<r<<" ]"<<endl;
        for (auto e : edges[x]){
            int u,v;
            tie(u,v) = e;
            cerr<<"< "<<u<<" , "<<v<<" >"<<endl;
        }
        if (l == r)return;
        int mid = l + r >> 1;
        debug(x<<1,l,mid);
        debug(x<<1|1,mid+1,r);
    }
}segtree;
map<pair<int,int>,vector<int> > mp;
int main(){
    int n,q;
    cin>>n>>q;
    for (int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if (u > v)swap(u,v);
        mp[make_pair(u,v)].push_back(i);
    }
    for (auto pr : mp){
        vector<int> & ts = pr.second;
        if (ts.size() & 1){
            ts.push_back(q+1);
        }
        for (int i=0;i<ts.size();i+=2){
            int st = ts[i];
            int ed = ts[i+1] - 1;
            segtree.put(1, 1, q, st, ed, pr.first);
        }
    }
    //  segtree.debug(1,1,q);
    segtree.dfs(1, 1, q);
    for (int i=1;i<=q;i++){
        puts(ans[i]?YES:NO);
    }
    return 0;
}
