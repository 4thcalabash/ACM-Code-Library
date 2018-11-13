// Created by calabash_boy on 18-7-24.
//他的名字是笛卡尔树。
#include<bits/stdc++.h>
using namespace std;
#define OPENSTACK
const int maxn = 1e6+100;
const int mod = 1e9+7;
typedef long long LL;
int stk[maxn],top,sz[maxn];
int l[maxn],r[maxn],rt,n;
pair<int,int> a[maxn];
LL inv[maxn],fac[maxn],inv_fac[maxn];
bool vis[maxn];
/* l 左儿子 r 右儿子 rt根*/
void build(){
    top=0;
    for (int i=1;i<=n;i++) l[i]=r[i]=vis[i] =0;
    for (int i=1;i<=n;i++){
        int k = top;
        while (k&&a[i]<a[stk[k-1]])k--;
        if (k) r[stk[k-1]] = i;
        if (k<top) l[i] = stk[k];
        stk[k++] =i;top = k;
    }
    for (int i=1;i<=n;i++) vis[l[i]] = vis[r[i]] =1;
    for (int i=1;i<=n;i++){
        if (!vis[i]){
            rt = i;
            break;
        }
    }
}
LL power(LL x,LL y){
    LL res =1;
    while (y){
        if (y&1)res = res*x%mod;
        y>>=1;
        x = x*x%mod;
    }
    return res;
}
inline LL C(int n,int m){
    return fac[n]*inv_fac[m]%mod*inv_fac[n-m]%mod;
}
int dfs(int u){
    sz[u]=1;int ans =1;
    if (l[u])ans=1LL*ans*dfs(l[u])%mod;
    if (r[u])ans = 1LL*ans*dfs(r[u])%mod;
    sz[u]+=sz[l[u]]+sz[r[u]];
    return 1LL*ans*C(sz[u]-1,sz[l[u]])%mod;
}
void Main(){
    inv[1]=fac[1]=fac[0]=1;
    for (int i=2;i<maxn;i++)fac[i] = fac[i-1]*i%mod,inv[i] = inv[mod%i]*(mod-mod/i)%mod;
    inv_fac[maxn-1] = power(fac[maxn-1],mod-2);
    for (int i=maxn-2;i>=0;i--){
        inv_fac[i] = inv_fac[i+1]*(i+1)%mod;
    }
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;scanf("%d", &x);
            a[i] = {-x, i};
        }
        build();
        printf("%d\n", inv[2] * n % mod * power(fac[n], mod - 2) % mod * dfs(rt) % mod);
    }
}
int main(){
#ifdef OPENSTACK
    int size = 70 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
#if (defined _WIN64) or (defined __unix)
    __asm__("movq %0, %%rsp\n" :: "r"(p));
#else
    __asm__("movl %0, %%esp\n" :: "r"(p));
#endif
#endif
    Main();
#ifdef OPENSTACK
    exit(0);
#else
    return 0;
#endif
}