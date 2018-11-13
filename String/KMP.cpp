// Created by calabash_boy on 18-7-23.
//最小权值和 二维循环节
//找到最小 每行公共循环节+每列公共循环节。
//单调队列找固定大小矩形最小权值和。
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
struct KMP{
    int nxt[maxn];int len;
    char t[maxn];
    void clear(){
        len =nxt[0] = nxt[1] =0;
    }
    /* 1-bas */
    /* 注意在ss结尾添加‘\0’ */
    void init(char* ss){
        len = strlen(ss+1);
        memcpy(t,ss,(len+2)*sizeof(char));
        for (int i=2;i<=len;i++){
            nxt[i] = nxt[i-1];
            while (nxt[i]&&ss[i]!=ss[nxt[i]+1]) nxt[i] = nxt[nxt[i]];
            nxt[i]+=(ss[i]==ss[nxt[i]+1]);
        }
    }
    /* 求所有在ss串中的start_pos. 如果first_only设置为true，则只返回第一个位置*/
    vector<int> match(char *ss,bool first_only = false){
        int len_s = strlen(ss+1);
        vector<int> start_pos(0);
        for (int i=1,j=1;i<=len_s;){
            while (j!=1 && ss[i] != t[j])j = nxt[j-1]+1;
            if (ss[i] == t[j]) j++,i++;
            else i++;
            if (j == len+1){
                start_pos.push_back(i-j+1);
                if (first_only)return start_pos;
                j = nxt[len]+1;
            }
        }
        return start_pos;
    }
    void debug(){
        for (int i=0;i<=len;i++){
            printf("[debug] nxt[%d]=%d\n",i,nxt[i]);
        }
    }
    /* 循环周期 形如 acaca 中 ac 是一个合法周期 */
    vector<int> periodic(){
        vector<int> ret;
        int now = len;
        while (now){
            now = nxt[now];
            ret.push_back(len-now);
        }
        return ret;
    }
    /* 循环节 形如 acac 中ac、acac是循环节，aca不是*/
    vector<int> periodic_loop(){
        vector<int>ret ;
        for (int x :periodic()){
            if (len%x==0)ret.push_back(x);
        }
        return ret;
    }
    int min_periodic_loop(){
        return periodic_loop()[0];
    }
}kmper;
vector<string> s;
vector<vector<int> > a,maxVal;
int cnt1[maxn],cnt2[maxn],n,m;
char S[maxn];
pair<int,int> pq[maxn];int l,r;
int main(){
    cin>>n>>m;
    s.resize(n+1);
    maxVal.resize(n+1);
    for (int i=1; i<=n;i++){
        cin>>s[i];
    }
    a.resize(n+1);
    for (int i=1;i<=n;i++){
        a[i].resize(m+1);
        maxVal[i].resize(m+1);
        for (int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    int p,q;kmper.clear();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            S[j] = s[i][j-1];
        }
        S[m+1]='\0';
        kmper.init(S);
        for (int x:kmper.periodic()){
            cnt1[x]++;
        }
    }
    for (int j=1;j<=m;j++){
        for (int i=1;i<=n;i++){
            S[i] = s[i][j-1];
        }
        S[n+1]='\0';
        kmper.init(S);
        for (int x:kmper.periodic()){
            cnt2[x]++;
        }
    }
    for (int i=maxn;i>=1;i--){
        if (cnt1[i]==n){ q = i; }
        if (cnt2[i]==m){ p=i; }
    }
    for (int i=1;i<=n;i++){
        l = 0,r=0;
        for (int j=1;j<=m;j++){
            while (r>l&&pq[l].second<=j-q)l++;
            while (r>l&&pq[r-1].first<=a[i][j])r--;
            pq[r++] = {a[i][j],j};
            if (j>=q){
                maxVal[i][j-q+1] = pq[l].first;
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int j=1;j<=m-q+1;j++){
        l=r=0;
        for (int i=1;i<=n;i++){
            while (r>l&&pq[l].second<=i-p)l++;
            while (r>l&&pq[r-1].first<=maxVal[i][j])r--;
            pq[r++] = {maxVal[i][j],i};
            if (i>=p){
                ans = min(ans,pq[l].first);
            }

        }
    }
    cout<<1LL*(p+1)*(q+1)*ans<<endl;
    return 0;
}