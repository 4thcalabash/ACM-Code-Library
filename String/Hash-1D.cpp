//
// Created by calabash_boy on 18-6-1.
// CF 985F
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+100;
typedef unsigned long long ULL;
int n,q;
char s[maxn];
/*
 * HASH TIME
 */
const int HASH_CNT = 2;
ULL hashV1[26],hashV2[26];
/*
 * char* 1-bas
 * sum[i] = s[i]+s[i-1]*Seed+s[i-2]*Seed^2+...+s[1]*Seed^(i-1)
 */
ULL Seed_Pool[]={146527,19260817};
ULL Mod_Pool[]={1000000009,998244353};
struct Hash_1D{
    /*
     * Add More Prime Num
     */

    ULL Seed,Mod;
    ULL bas[maxn];
    ULL sum[26][maxn];
    void init(int seedIndex,int modIndex){
        Seed = Seed_Pool[seedIndex];
        Mod = Mod_Pool[modIndex];
        bas[0]=1;
        for (int i=1;i<=n;i++){
            bas[i] = bas[i-1]*Seed%Mod;
        }
        for (int i=1;i<=n;i++){
            for (int j=0;j<26;j++){
                sum[j][i] = (sum[j][i-1]*Seed%Mod+(s[i]==j+'a'))%Mod;
            }
        }
    }
    ULL getHash(int ch,int l,int r){
        return (sum[ch][r]-sum[ch][l-1]*bas[r-l+1]%Mod+Mod)%Mod;
    }
}hasher[HASH_CNT];
bool isSame(int l1,int r1,int l2,int r2){
    for (int h=0;h<HASH_CNT;h++){
        for (int i=0;i<26;i++){
            hashV1[i] = hasher[h].getHash(i,l1,r1);
            hashV2[i] = hasher[h].getHash(i,l2,r2);
        }
        sort(hashV1,hashV1+26);
        sort(hashV2,hashV2+26);
        for (int i=0;i<26;i++){
            if(hashV1[i]!=hashV2[i]){
                return false;
            }
        }
    }
    return true;
}
void solve(){
    int x,y,len;
    scanf("%d%d%d",&x,&y,&len);
    if(isSame(x,x+len-1,y,y+len-1)){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
}
int main(){
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    /*
     * Free Combination ex.init(i,j)
     */
    for (int i=0;i<HASH_CNT;i++){
        hasher[i].init(i,i);
    }
    while (q--){
        solve();
    }
    return 0;
}