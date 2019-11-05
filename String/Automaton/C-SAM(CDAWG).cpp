// Created by calabash_boy on 2019/11/5.
// 求后缀树的每条边代表字符串的本质不同子串个数的和
// 后缀树边上字符串unique之后总长度为3*n.
// unique的结果与压缩sam上的边相同。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 100;
typedef long long ll;
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    bool vis[maxn*2];
    int dirNxt[maxn*2][26];
    int dirLen[maxn*2][26];
    int ed[maxn*2];
    vector<pair<int,int> > lens[maxn*2];
    int last,cnt;
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(string s){
        for (int c : s)add(c - 'a');
        for (int i=0;i<=cnt;i++){
            vis[i] = false;
            ed[i] = -1;
            lens[i].clear();
            memset(dirLen[i],0,sizeof dirLen[i]);
            memset(dirNxt[i],0,sizeof dirNxt[i]);
        }
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
    int find_nxt(int u){
        int res = -1;
        for (int ch = 0;ch < 26;ch ++){
            int v = nxt[u][ch];
            if (!v)continue;
            if (res == -1)res = ch;
            else return -1;
        }
        return res;
    }
    void dfs(int u){
        vis[u] = true;
        for (int ch = 0;ch < 26;ch ++){
            int v = nxt[u][ch];
            if (!v)continue;
            if (!vis[v])dfs(v);
            int dirch = find_nxt(v);
            if(dirch == -1){
                dirNxt[u][ch] = v;
                dirLen[u][ch] = 1;
            }else{
                dirNxt[u][ch] = dirNxt[v][dirch];
                dirLen[u][ch] = dirLen[v][dirch] + 1;
            }
            if (find_nxt(u) == -1 or u == 1)lens[dirNxt[u][ch]].push_back(make_pair(dirLen[u][ch],u == 1?1:l[u] - l[fa[u]]));
        };
    }
    void build(string s,Suffix_Automaton & sam_t){
        int temp = 1;
        for(int i=0;i<s.length();i++){
            temp = nxt[temp][s[i] - 'a'];
            int t = temp;
            while (ed[t] == -1 && t != 1){
                ed[t] = i;
                t = fa[t];
            }
        }
        ll ans = 0;
        for (int i=2;i<=cnt;i++){
            if (lens[i].empty())continue;
            int Mx = 0;
            for (auto x : lens[i])Mx = max(Mx,x.first);
            string t = s.substr(ed[i] - Mx + 1,Mx);
            sam_t.clear();
            reverse(t.begin(),t.end());
            vector<ll> cnt(1,0);
            for (int c : t){
                sam_t.add(c - 'a');
                cnt.push_back(cnt.back() + sam_t.l[sam_t.last] - sam_t.l[sam_t.fa[sam_t.last]]);
            }
            for (auto x : lens[i])ans += cnt[x.first] * x.second;
        }
        cout<<ans<<endl;
    }
}sam,temp_sam;
int main(){
    int T;
    cin>>T;
    while (T--){
        string s;
        cin>>s;
        sam.clear();
        sam.init(s);
        sam.dfs(1);
        sam.build(s,temp_sam);
    }
    return 0;
}
