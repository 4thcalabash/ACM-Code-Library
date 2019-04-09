// Created by calabash_boy on 18-6-4.
//SPOJ substring
// calc ans_i=长度=i的所有子串，出现次数最多的一种出现了多少次。
#include<bits/stdc++.h>
#define RIGHT
//RIGHT: parent树的dfs序上主席树，求每个点的Right集合
using namespace std;
const int maxn = 25e4+100;
struct Node{int L,R,val;}Tree[maxn*40];
#ifdef RIGHT
struct Chairman_Tree{
    int cnt = 0;
    int root[maxn*2];
    void init(){
        memset(root,0,sizeof root);
        cnt =0;
    }
    /* 建T0空树 */
    int buildT0(int l, int r){
        int k = cnt++;
        Tree[k].val =0;
        if (l==r) return k;
        int mid = l+r >>1;
        Tree[k].L = buildT0(l, mid);Tree[k].R = buildT0(mid + 1, r);
        return k;
    }
    /* 上一个版本节点P，【ppos】+=del 返回新版本节点*/
    int update (int P,int l,int r,int ppos,int del){
        assert(cnt < maxn*50);
        int k = cnt++;
        Tree[k].val = Tree[P].val +del;
        if (l==r) return k;
        int mid = l+r >>1;
        if (ppos<=mid){
            Tree[k].L = update(Tree[P].L,l,mid,ppos,del);
            Tree[k].R = Tree[P].R;
        }else{
            Tree[k].L = Tree[P].L;
            Tree[k].R = update(Tree[P].R,mid+1,r,ppos,del);
        }
        return k;
    }
    int query(int PL,int PR,int l,int r,int L,int R){
        if (l>R || L>r)return 0;
        if (L <= l && r <= R)return Tree[PR].val - Tree[PL].val;
        int mid = l + r >> 1;
        return query(Tree[PL].L,Tree[PR].L,l,mid,L,R) + query(Tree[PL].R,Tree[PR].R,mid+1,r,L,R);
    }
}tree;
#endif
char s[maxn];int n,ans[maxn];
/*注意需要按l将节点基数排序来拓扑更新parent树*/
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    //extension
    int cntA[maxn*2],A[maxn*2];/*辅助拓扑更新*/
    int num[maxn*2];/*每个节点代表的所有串的出现次数*/
#ifdef RIGHT
    vector<int> E[maxn*2];
    int dfsl[maxn*2],dfsr[maxn*2],dfn;
    int pos[maxn*2];
    int end_pos[maxn*2];//1基
#endif
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');s++;
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
    void build(){
        memset(cntA,0,sizeof cntA);
        memset(num,0,sizeof num);
        for (int i=1;i<=cnt;i++)cntA[l[i]]++;
        for (int i=1;i<=cnt;i++)cntA[i]+=cntA[i-1];
        for (int i=cnt;i>=1;i--)A[cntA[l[i]]--] =i;
        /*更行主串节点*/
        int temp=1;
        for (int i=0;i<n;i++){
            num[temp = nxt[temp][s[i]-'a'] ]=1;
        }
        /*拓扑更新*/
        for (int i=cnt;i>=1;i--){
            //basic
            int x = A[i];
            num[fa[x]]+=num[x];
            //special
            ans[l[x]] = max(ans[l[x]],num[x]);
        }
        //special
        for (int i=l[last];i>1;i--){
            ans[i-1] = max(ans[i-1],ans[i]);
        }
    }

#ifdef RIGHT
    int get_right_between(int u,int l,int r){
        return tree.query(tree.root[dfsl[u] - 1],tree.root[dfsr[u]],1,::n,l,r);
    }
    void dfs(int u){
        dfsl[u] = ++ dfn;
        pos[dfn] = u;
        for (int v : E[u]){
            dfs(v);
        }
        dfsr[u] = dfn;
    }
    void extract_right(){
        int temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][s[i] - 'a'];
            end_pos[temp] = i+1;
        }
        for (int i=2;i<=cnt;i++){
            E[fa[i]].push_back(i);
        }
        dfn = 0;
        dfs(1);
        tree.root[0] = tree.buildT0(1,n);
        for (int i=1;i<=cnt;i++){
            int u = pos[i];
            if (end_pos[u]){
                int idx = end_pos[u];
                tree.root[i] = tree.update(tree.root[i-1],1,n,idx,1);
            }else{
                tree.root[i] = tree.root[i-1];
            }
        }
    }
#endif
    void debug(){
        for (int i=cnt;i>=1;i--){
            printf("num[%d]=%d l[%d]=%d fa[%d]=%d\n",i,num[i],i,l[i],i,fa[i]);
        }
    }
}sam;
int main(){
    scanf("%s",s);
    /* calc n must before sam.init()*/
    n = strlen(s);
    sam.init(s);
    sam.build();
    for (int i=1;i<=n;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}