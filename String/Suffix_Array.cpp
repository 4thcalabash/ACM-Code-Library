/*
 * for each 2-power string.
 * let its length is 2L. add edge of length w[L] between every i and i + L.
 * calculate the spanning forests.
 */
#include <bits/stdc++.h>
#define rank rkrkrk
//#define _DEBUG
#define RMQ
using namespace std;
const int maxn = 3e5+100;
int w[maxn];
struct Run{
    int l,r,k;
};
struct UFS {
    int fa[maxn];
    void init(int n) { iota(fa, fa + n + 1, 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        fa[u] = v;
        return u != v;
    }
} ufs[20];

int unite(int u, int v, int k) {
    if (ufs[k].unite(u, v)) {
        if (k == 0) return 1;
        return unite(u, v, k - 1) + unite(u + (1<<(k-1)), v + (1<<(k-1)), k - 1);
    } else return 0;
}

long long merge(int u, int v, int l) {
    int k = log2(l);
    int ret =  unite(u, v, k) +
               unite(u + l - (1<<k), v + l - (1<<k), k);
    return ret;
}
struct SA{
#ifndef RMQ
    struct Segment_Tree{
        int min_val[maxn*4];
        void up(int x){
            min_val[x] = min(min_val[x<<1],min_val[x<<1|1]);
        }
        void build(int x,int l,int r,int*h){
            if (l == r){
                min_val[x] = h[l];
                return;
            }
            int mid = l + r >>1;
            build(x<<1,l,mid,h);
            build(x<<1|1,mid+1,r,h);
            up(x);
        }
        int query(int x,int l,int r,int L,int R){
            if (l > R || L > r)return 0x3f3f3f3f;
            if (L<= l && r <= R)return min_val[x];
            int mid = l + r >> 1;
            return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
        }
    }segtree;
#else
    int st[maxn][20];
    void st_init(int n,int*h){
        for (int i=1;i<=n;i++){
            st[i][0] = h[i];
        }
        for (int j=1;(1<<j)<=n;j++){
            for (int i=1;i<=n-(1<<j)+1;i++){
                st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
    }
#endif
    int cntA[maxn],cntB[maxn],tsa[maxn],A[maxn],B[maxn];
    int sa[maxn],rank[maxn],height[maxn];
    void get_sa(int * ch,int n){
        ch[0] = ch[n+1] = -1;
        for (int i=0;i<=n;i++)cntA[i] = 0;
        for (int i=1;i<=n;i++)cntA[ch[i]]++;
        for (int i=1;i<=n;i++)cntA[i] += cntA[i-1];
        for (int i=n;i>=1;i--)sa[cntA[ch[i]]--] = i;
        rank[sa[1]] = 1;
        for (int i=2;i<=n;i++){
            rank[sa[i]] = rank[sa[i-1]];
            if (ch[sa[i]] != ch[sa[i-1]])rank[sa[i]] ++;
        }
        for (int l=1;rank[sa[n]]<n;l<<=1){
            for (int i=0;i<=n;i++)cntA[i] = cntB[i] = 0;
            for (int i=1;i<=n;i++){
                cntA[A[i] = rank[i]] ++;
                cntB[B[i]=(i+l<=n)?rank[i+l]:0]++;
            }
            for (int i=1;i<=n;i++)cntB[i] += cntB[i-1];
            for (int i=n;i>=1;i--)tsa[cntB[B[i]]--] = i;
            for (int i=1;i<=n;i++)cntA[i] += cntA[i-1];
            for (int i=n;i>=1;i--)sa[cntA[A[tsa[i]]]--] = tsa[i];
            rank[sa[1]] = 1;
            for (int i=2;i<=n;i++){
                rank[sa[i]] = rank[sa[i-1]];
                if (A[sa[i]] != A[sa[i-1]] || B[sa[i]] != B[sa[i-1]])rank[sa[i]] ++;
            }
        }
    }
    void get_height(int *ch,int n){
        get_sa(ch,n);
        sa[0] = rank[0] = 0;
        for (int i=1,j=0;i<=n;i++){
            if (j) j--;
            while (ch[i+j] == ch[sa[rank[i]-1]+j])j++;
            height[rank[i]] = j;
        }
#ifdef _DEBUG
        for (int i=1;i<=n;i++){
            printf("height[%d]=%d\n",i,height[i]);
        }
#endif
#ifndef RMQ
        segtree.build(1,1,n,height);
#else
        st_init(n,height);
#endif
    }
    int get_lcp(int x,int y,int n){
        int rkx = rank[x];
        int rky = rank[y];
        if (rkx>rky)swap(rkx,rky);
        rkx++;
#ifndef RMQ
        int lcp = segtree.query(1,1,n,rkx,rky);
#else
        int k = log2(rky - rkx+1);
        int lcp = min(st[rkx][k],st[rky - (1<<k)+1][k]);
#endif

#ifdef _DEBUG
        printf("[get_lcp] x=%d y=%d rkx=%d,rky=%d,lcp =%d\n",x,y,rkx,rky,lcp);
#endif
        return lcp;
    }
}sa1,sa2;
int ch2[maxn];
vector<Run> get_run(int*ch,int n){
    sa1.get_height(ch,n);
    for (int i=0;i<=n+1;i++){
        ch2[i] = ch[i];
    }
    reverse(ch2+1,ch2+1+n);
    sa2.get_height(ch2,n);
    vector<Run> result(0);
    int len_max = n/2;
    for (int len = 1;len <=len_max;len ++){
        //get_len_run
        for (int i=1;i<=n;i+=len){
            int j = i+len;
            if (j >n)break;
            int lcp = sa1.get_lcp(i,j,n);
            int lcs = sa2.get_lcp(n+1-i,n+1-j,n);
            lcp = min(lcp,len);
            lcs = min(lcs,len);
            assert(j+lcp-1<=n);
            assert(i-lcs+1>=1);
#ifdef _DEBUG
            printf("i=%d,j=%d,len=%d,lcp=%d,lcs=%d\n",i,j,len,lcp,lcs);
#endif
            if (lcp + lcs - 1 < len)continue;
            int L = j-lcs+1;
            int R = j + lcp -1;
            result.push_back((Run){L,R,len});
        }
    }
#ifdef _DEBUG
    for (Run run : result){
        printf("[run]: l=%d, r=%d,k=%d\n",run.l,run.r,run.k);
    }
#endif
    return result;
}
int n;
typedef long long ll;
ll spanning_forest(vector<Run> &runs){
    sort(runs.begin(),runs.end(),[](Run x,Run y){
        return w[x.k] < w[y.k];
    });
    ll ans = 0;
    for (auto& R : runs) {
        int l = R.l, r = R.r;
        ans += 1ll * merge(l - R.k, l, r - l + 1) * w[R.k];
    }
    return ans;
}
int ch[maxn];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        for (int i = 0; i < 20 ; i++) ufs[i].init(n);
        ch[n+1] = -1;
        ch[0] = -1;
        for (int i=1;i<=n;i++){
            scanf("%d",ch+i);
        }
        int m = n/2;
        for (int i=1;i<=m;i++){
            scanf("%d",w+i);
        }
        vector<Run> all_run = get_run(ch,n);
        printf("%lld\n",spanning_forest(all_run));
    }
    return 0;
}
