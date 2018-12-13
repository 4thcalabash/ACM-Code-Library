// Created by calabash_boy on 18-6-1.
// CF 1003F
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 305*305;
/* 字符集大小 */
const int sigma = maxn;
/* hash次数 */
const int HASH_CNT = 2;
int n;
int s[maxn];
 /* char* 1-bas
 * sum[i] = s[i]+s[i-1]*Seed+s[i-2]*Seed^2+...+s[1]*Seed^(i-1)*/
ULL Prime_Pool[] = {1998585857ul,23333333333ul};
ULL Seed_Pool[]={911,146527,19260817,91815541};
ULL Mod_Pool[]={29123,998244353,1000000009,4294967291ull};
struct Hash_1D{
    ULL Seed,Mod;
    ULL bas[maxn];ULL sum[maxn];
    int perm[sigma];
    void init(int seedIndex,int modIndex){
        Seed = Seed_Pool[seedIndex];
        Mod = Mod_Pool[modIndex];
        bas[0]=1;
        for (int i=1;i<=n;i++){
            bas[i] = bas[i-1]*Seed%Mod;
        }
        for (int i=1;i<=n;i++){
            sum[i] = (sum[i-1]*Seed%Mod+s[i])%Mod;
        }
    }
    /*random_shuffle 离散化id，防止kill_hash*/
    void indexInit(int seedIndex,int modIndex){
        for (int i=1;i<n;i++){
            perm[i]=i;
        }
        random_shuffle(perm+1,perm+1+sigma);
        Seed = Seed_Pool[seedIndex];
        Mod = Mod_Pool[modIndex];
        bas[0]=1;
        for (int i=1;i<=n;i++){
            bas[i] = bas[i-1]*Seed%Mod;
        }
        for (int i=1;i<=n;i++){
            sum[i] = (sum[i-1]*Seed%Mod+perm[s[i]])%Mod;
        }
    }
    ULL getHash(int l,int r){
        return (sum[r]-sum[l-1]*bas[r-l+1]%Mod+Mod)%Mod;
    }
}hasher[HASH_CNT];
map<pair<pair<ULL,ULL>,int>,int>veid;int vecnt;
map<string,int>id;int idcnt;
vector<int> pos[maxn];
string a[maxn];
int sumL[maxn];
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        if (!id[a[i]])id[a[i]] = ++idcnt;
        s[i] = id[a[i]];
        sumL[i] = sumL[i-1]+a[i].size();
    }
    for (int i=0;i<HASH_CNT;i++){
        hasher[i].indexInit(i,i);
    }
    int ans = sumL[n]+n-1;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            ULL hash1 = hasher[0].getHash(i,j);
            ULL hash2 = hasher[1].getHash(i,j);
            int len = j-i+1;
            pair<pair<ULL,ULL>,int> x = {{hash1,hash2},len};
            if (veid[x]==0)veid[x] = ++vecnt;
            pos[veid[x]].push_back(i);
        }
    }
    int maxDelta =0;
    for (auto x:veid){
        int len = x.first.second;
        int i = x.second;
        sort(pos[i].begin(),pos[i].end());
        int num =0;
        for (int j=0,last = -maxn;j<pos[i].size();j++){
            if (pos[i][j]>=last+len){
                last = pos[i][j];
                num++;
            }
        }
        if (num==1)continue;
        int cost1 = sumL[pos[i][0]+len-1]-sumL[pos[i][0]-1]+len-1;
        int cost2 = len;
        int tempDelta = (cost1-cost2)*num;
        maxDelta = max(maxDelta,tempDelta);
    }
    cout<<ans-maxDelta<<endl;
    return 0;
}