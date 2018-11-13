// Created by calabash_boy on 18-8-17.
//UOJ 310
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1048576;;
const int MOD = 998244353;
const int INV2 = (MOD+1)>>1;
const int INV4 = 1LL*INV2*INV2%MOD;
int a[N];
int n;
//xor fwt : A[i] = \sigma{-1^([i&j])*a[j]}   [x]:count of 1-bit
void FWT(int *a,int n,int r){
    for (int i=1;i<n;i<<=1){
        for (int j=0;j<n;j+=(i<<1)){
            for (int k =0;k<i;k++){
                int x = a[j+k];int y = a[j+k+i];
                if (r){
                    a[j+k] = (x+y)%MOD;
                    a[j+k+i] = (x-y+MOD)%MOD;
                }else{
                    a[j+k] = 1LL*(x+y)*INV2%MOD;
                    a[j+k+i] = 1LL*(x-y+MOD)*INV2%MOD;
                }
            }
        }
    }
}
LL pow_mod(LL x,LL y){
    LL ret = 1;
    for (;y;y>>=1){if (y&1) ret = ret*x%MOD;x = x*x%MOD;}
    return ret;
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        a[x]++;
    }
    FWT(a,N,1);
    for(int i=0;i<N;i++){
        a[i] = (n+2*a[i])%MOD;
        int cnt3 = 1LL*(a[i]+n)%MOD*INV4%MOD;
        int cnt1 = n-cnt3;
        a[i] = pow_mod(3,cnt3);
        if (cnt1&1)a[i] = MOD-a[i];
    }
    FWT(a,N,0);
    printf("%d\n",(a[0]+MOD-1)%MOD);
    return 0;
}