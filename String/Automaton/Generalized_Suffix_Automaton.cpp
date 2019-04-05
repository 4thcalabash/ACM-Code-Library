// Created by calabash_boy on 19-4-5.
//wf2019 first of her name
//build sam using trie
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
typedef long long ll;
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    vector<int> E[maxn*2];
    int Num[maxn*2];
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    int add(int pre,int c,int num){
        last = pre;
        int p = last;
        int np = ++cnt;
        Num[np] = num;
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
        return np;
    }
    int dfsl[maxn*2],dfsr[maxn*2];
    int dfn = 0;
    ll sum[maxn*2];
    void dfs(int u){
        dfsl[u] = ++dfn;
        sum[dfn] = Num[u];
        for (int v : E[u]){
            dfs(v);
        }
        dfsr[u] = dfn;
    }
    void build(){
        for (int i=2;i<=cnt;i++){
            E[fa[i]].push_back(i);
        }
        dfs(1);
        for (int i=1;i<=cnt;i++){
            sum[i] += sum[i-1];
        }
    }
    void query(char * s){
        int temp = 1;
        while (*s){
            int ch = *s - 'A';
            if (!nxt[temp][ch]){
                printf("0\n");
                return;
            }
            temp = nxt[temp][ch];
            s++;
        }
        ll ans = sum[dfsr[temp]] - sum[dfsl[temp] - 1];
        printf("%lld\n",ans);
    }
}sam;
struct Trie{
    int Root = 1;
    int cnt = 2;
    int nxt[maxn][26];
    int num[maxn];
    int sam_pos[maxn];
    int add(int p,int ch){
        if (!nxt[p][ch]){
            nxt[p][ch] = cnt++;
        }
        int now = nxt[p][ch];
        num[now] ++;
        return now;
    }
    void bfs(){
        queue<int> Q;
        Q.push(1);
        sam_pos[1] = 1;
        while (!Q.empty()){
            int head = Q.front();
            Q.pop();
            for (int i=0;i<26;i++){
                if (!nxt[head][i])continue;
                int now = nxt[head][i];
                sam_pos[now] = sam.add(sam_pos[head],i,num[now]);
                Q.push(now);
            }
        }
    }
}trie;
int trie_pos[maxn];
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    trie_pos[0] = 1;
    for (int i=1;i<=n;i++){
        static char s[5];
        int p;
        scanf("%s%d",s,&p);
        int ch = s[0] - 'A';
        trie_pos[i] = trie.add(trie_pos[p],ch);
    }
    trie.bfs();
    sam.build();
    for (int i=0;i<k;i++){
        static char t[maxn];
        scanf("%s",t);
        int N = strlen(t);
        reverse(t,t+N);
        sam.query(t);
    }
    return 0;
}