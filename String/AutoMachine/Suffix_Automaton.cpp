//
// Created by calabash_boy on 18-6-4.
//SPOJ substring
// calc ans_i=长度=i的所有子串，出现次数最多的一种出现了多少次。
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 25e4+100;
char s[maxn];
int n;
int ans [maxn];
/*注意需要按l将节点基数排序来拓扑更新parent树*/
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    //extension
    int cntA[maxn*2],A[maxn*2];/*辅助拓扑更新*/
    int num[maxn*2];/*每个节点代表的所有串的出现次数*/
    Suffix_Automaton(){
        clear();
    }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;
        last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];
                fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void build(){
        memset(cntA,0,sizeof cntA);
        memset(num,0,sizeof num);
        for (int i=1;i<=cnt;i++)cntA[l[i]]++;
        for (int i=1;i<=n;i++)cntA[i]+=cntA[i-1];
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
    sam.clear();
    sam.init(s);
    sam.build();
    for (int i=1;i<=n;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}