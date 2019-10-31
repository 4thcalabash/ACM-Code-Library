// Created by calabash_boy on 2019/10/28.
// CF 100962D 求区间border series，最大border。
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define rank rkrkrk
using namespace std;
const int maxn = 4e5 + 100;
const int maxlog = 19;
struct Sequence{
    /** l + k*d <=r **/
    int l,r,d;
    Sequence(int ll = 0,int rr = 0,int dd = 0){
        l = ll;r = rr;d = dd;
    }
    Sequence(const vector<int> & pos){
        if (pos.empty()){
            l = r = d = 0;
        }else if (pos.size() == 1){
            l = pos.front();
            r = pos.front();
            d = 1;
        }else{
            l = pos.front();
            r = pos.back();
            d = pos[1] - pos[0];
        }
    }
    bool has(int x){
        return d and x >= l and x <= r and x % d == l % d;
    }
    int count(){
        if (d == 0)return 0;
        return (r - l) / d + 1;
    }
    vector<int> to_list(){
        vector<int> list(0);
        if (d == 0)return list;
        for (int i=l;i<=r;i+=d)list.push_back(i);
        return list;
    }
};
Sequence operator -(int X, Sequence S){return Sequence(X - S.r,X - S.l, S.d);}
Sequence operator -(Sequence S, int X){return Sequence(S.l - X, S.r - X, S.d);}
Sequence operator &(Sequence S1, Sequence S2){
    int cnt1 = S1.count(), cnt2 = S2.count();
    if (cnt1 == 0 || cnt2 == 0) return Sequence(0,0,0);
    if (cnt1 > cnt2){
        swap(S1,S2);swap(cnt1,cnt2);
    }
    if (cnt1 < 3){
        vector<int> pos(0);
        for (int x : S1.to_list()){
            if (S2.has(x)) pos.push_back(x);
        }
        return Sequence(pos);
    }else{
        if (S1.d == S2.d){
            int l = max(S1.l,S2.l), r = min(S1.r,S2.r);
            if (r >= l && S1.l % S1.d == S2.l % S1.d)return Sequence(l,r,S1.d);
            else return Sequence(0,0,0);
        }else assert(0);
    }
}
struct Run{
    //S[l,r] is a run of period of length d.
    int l,r,d;
    Run(int ll = 0,int rr = 0,int dd = 0){
        l = ll;r = rr;d = dd;
    }
    bool operator < (const Run &other)const{
        if (l != other.l)return l < other.l;
        if (r != other.r)return r < other.r;
        if (d != other.d)return d < other.d;
        return false;
    }
    bool operator == (const Run &other)const{
        return l == other.l and r == other.r and d == other.d;
    }
};
struct Dictionary_of_Basic_Factories{
    /** 1-base **/
    int name[maxn][maxlog];int n;
    vector<vector<int> > pos[maxlog];
    int cntA[maxn],cntB[maxn],tsa[maxn],A[maxn],B[maxn];
    int sa[maxn],rank[maxn];
    int height[maxn];
    void clear(){
        for (int i=0;i<=max(n,'z' + 10);i++){
            cntA[i] = cntB[i] = tsa[i] = A[i] = B[i] = sa[i] = rank[i] = height[i] = 0;
            for (int k=0;k<maxlog;k++)name[i][k] = 0;
        }
        for (int k=0;k<maxlog;k++)pos[k].clear();
    }
    void init(char * ch,int n){
        ch[0] = ch[n+1] = '#'; this->n = n;
        for (int i=1;i<=n;i++)cntA[ch[i]]++;
        for (int i=1;i<maxn;i++)cntA[i] += cntA[i-1];
        for (int i=n;i>=1;i--)sa[cntA[ch[i]]--] = i;
        rank[sa[1]] = 1;
        for (int i=2;i<=n;i++){
            rank[sa[i]] = rank[sa[i-1]];
            if (ch[sa[i]] != ch[sa[i-1]])rank[sa[i]] ++;
        }
        pos[0].resize(rank[sa[n]] + 1,vector<int>(0));
        for (int i=1;i<=n;i++){
            name[i][0] = rank[i];
            pos[0][rank[i]].push_back(i);
        }
        for (int step = 1,l=1;l <= n;l<<=1,step ++){
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
            pos[step].resize(rank[sa[n]] + 1,vector<int> (0));
            for (int i = 1;i <=n;i++){
                name[i][step] = rank[i];
                pos[step][rank[i]].push_back(i);
            }
        }
    }
    void get_height(char *ch, int n){

        sa[0] = rank[0] = 0;
        for (int i=1,j=0;i<=n;i++){
            if (j)j--;
            while (ch[i+j] == ch[sa[rank[i]-1] +j])j++;
            height[rank[i]]= j;
        }
    }
    // get sequence [2^step,2^(step+1))
    Sequence get_seq(vector<int> & list, int l, int r){
        vector<int> pos(0);
        int idx = lower_bound(list.begin(),list.end(),l) - list.begin();
        while (idx < list.size() && pos.size() < 3 && list[idx] <= r){
            pos.push_back(list[idx]);idx ++;
        }
        if (pos.size() < 3)return Sequence(pos);
        else{
            int last = upper_bound(list.begin(),list.end(),r) - list.begin() - 1;
            int L = pos.front(), d = pos[1] - pos[0], R = list[last];
            return Sequence(L,R,d);
        }
    }
    Sequence get_border(int l,int r,int step){
        int len = r - l + 1;
        int baby = 1 << step, giant = min(len-1,(baby * 2-1));
        int namel = name[l][step], namer = name[r - baby + 1][step];
        Sequence seql = get_seq(pos[step][namel],r - giant + 1,r - baby + 1),
                seqr = get_seq(pos[step][namer],l,l + giant - baby);
        seql = (r + 1) - seql; seqr = seqr - (l -baby);
        return  seql & seqr;
    }
    /** return O(logn) border series of S[l,r].
     * Attention: can contain empty sequence (0,0,0)
     * if [2^i,2^(i+1)) border does not exist.*/
    vector<Sequence> get_border_series(int l,int r){
        vector<Sequence> ret(0);
        for (int step = 0;(1<<step) < r - l + 1;step++){
            ret.push_back(get_border(l,r,step));
        }
        return ret;
    }
    int get_biggest_border(int l,int r){
        int len = r - l + 1;
        for (int k = maxlog - 1; k >=0;k--){
            if ((1<<k) >= len)continue;
            Sequence seq = get_border(l,r,k);
            if (seq.r)return seq.r;
        }
        return 0;
    }
    int lcp(int x,int y){
        int len = 0;
        for (int k = maxlog-1;k>=0;k--){
            int LEN = 1<< k;
            if (x + LEN - 1 <= n and y + LEN - 1 <= n and name[x][k] == name[y][k]){
                len += 1<<k;
                x += 1<<k;
                y += 1<<k;
            }
        }
        return len;
    }
    int lcs(int x,int y){
        int len = 0;
        for (int k = maxlog-1;k>=0;k--){
            int LEN = 1 << k;
            if (x >= LEN and y >= LEN and name[x - LEN + 1][k] == name[y - LEN + 1][k]){
                len += LEN;
                x -= LEN;
                y -= LEN;
            }
        }
        return len;
    }
    vector<Run> get_all_runs(){
        // cerr<<n<<endl;
        vector<Run> run_list(0);
        for (int per = 1; per * 2 <= n; per ++){
            for (int pos = per;pos <= n;pos += per){
                int left = lcs(pos,pos + per);
                int right = lcp(pos,pos + per);
                if (left + right > per){
                    run_list.push_back(Run(pos - left + 1,pos + per + right - 1,per));
                }
            }
        }
        vector<Run> result(0);
        pair<int,int> pre = {-1,-1};
        for (auto run : run_list){
            pair<int,int> now = {run.l,run.r};
            if (pre != now){
                pre = now;
                result.push_back(run);
            }
        }
        return result;
    }
}dbf;
char s[maxn];
int n,q;
int main(){
    scanf("%d%d",&n,&q);
    scanf("%s",s + 1);
    dbf.init(s,n);
    while (q--){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",dbf.get_biggest_border(l,r));
    }
    return 0;
}