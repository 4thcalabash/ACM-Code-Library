// Created by calabash_boy on 18-7-7.
// max(XorSum(a_l^r))
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e6+100;
int bas[35],n,Cas;
const int INF = 2147483645;
struct Trie{
    int nxt[MAX<<2][2],l[MAX<<2];
    int cnt,ansl,ansr,ansv;
    void init(){
        cnt =ansv = 0;
        memset(nxt[0],0,sizeof (nxt[0]));
        memset(l,0x3f3f3f3f,sizeof(l));
    }
    int create(){
        cnt++;
        memset(nxt[cnt],0,sizeof (nxt[cnt]));
        return cnt;
    }
    void insert(int id,int x){
        int y = 0;
        for (int i=30;i>=0;i--){
            int t = x&bas[i];
            t>>=i;
            if (!nxt[y][t])nxt[y][t] = create();
            y = nxt[y][t];
        }
        l[y] = min(l[y],id);
    }
    void query(int id,int x){
        int y=0;  int res =0;
        for (int i=30;i>=0;i--){
            int t = x&bas[i];
            t>>=i;
            if (nxt[y][!t]){
                y =nxt[y][!t];
                res+=bas[i];
            }else{
                y = nxt[y][t];
            }
        }
        if (res==ansv){
            if (l[y]<ansl){
                ansl = l[y];  ansr = id;
            }
        }else if (res>ansv){
            ansv = res;
            ansl = l[y];
            ansr = id;
        }
    }
}trie;
int main(){
    bas[0] = 1;
    for (int i1=1;i1<=30;i1++)bas[i1] = bas[i1-1]<<1;
    scanf("%d",&Cas);
    for (int i=1;i<=Cas;i++){
        trie.init();  trie.insert(0,0);
        scanf("%d",&n);
        int sum=0;
        for (int j=1;j<=n;j++){
            int ai;
            scanf("%d",&ai);  sum^=ai;
            trie.query(j,sum);  trie.insert(j,sum);
        }
        printf("Case #%d:\n%d %d\n", i, trie.ansl + 1, trie.ansr);
    }
    return 0;
}