//树上回文自动机，每个点到根的路径代表一个字符串。
//强制在线增加叶子，求最大回文后缀。
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int lastans = 0;
const int maxn = 5e5+100;
int st[maxn][20];
int pos[maxn];
map<char,int> score;
char a[maxn];
int sum[maxn];
int get_anc(int x,int len){
    while (len){
        int bit = __builtin_ctz(len);
        x = st[x][bit];
        len ^= (1 << bit);
    }
    return x;
}
int Damage[maxn];
struct Palindromic_AutoMaton{
    //basic
    int now;
    int nxt[maxn][26],fail[maxn],l[maxn],tot;
    int damage[maxn];
    int damage_sum[maxn];
    int total[maxn];
    int Link[maxn][26];
    // extension
    int num[maxn];/*节点代表的所有回文串出现次数*/
    void clear(){
        //1节点：奇数长度root 0节点：偶数长度root
        l[1]=-1;
        fail[0] = tot = now =1;
        l[0]=0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
        for (int i = 0;i < 26;i ++)Link[1][i]=1,Link[0][i] = 1;
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int ll){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=num[tot]=0;
        l[tot]=ll;
        return tot;
    }
    int add(int i,int F,int last,int ch){
        int cur = Link[last][ch];
        if (a[get_anc(i,l[last]+1)] - 'A' == ch){
            cur = last;
        }
        if(!nxt[cur][ch]){
            int tt = newnode(l[cur]+2);
            fail[tt] = nxt[Link[cur][ch]][ch];
            nxt[cur][ch] = tt;
            memcpy(Link[tt],Link[fail[tt]],sizeof Link[tt]);

            int u = get_anc(i,l[fail[tt]]);

            Link[tt][a[u] - 'A'] = fail[tt];

            damage[tt] = sum[i] - sum[get_anc(i,l[tt])];
            damage_sum[tt] = (damage_sum[fail[tt]] + damage[tt])% mod;
        }
        last = nxt[cur][ch];num[last]++;
        return last;
    }
}pam;
char buf[10];
int main(){
    int _;
    scanf("%d",&_);
    score['A'] = _;
    scanf("%d",&_);
    score['C'] = _;
    scanf("%d",&_);
    score['G'] = _;
    scanf("%d",&_);
    score['U'] = _;
    scanf("%s",buf);
    a[1] = buf[0];
    a[0] = 'Z';
    sum[1] = score[buf[0]];
    pos[0] = 1;
    pos[1] = pam.add(1,0,1,buf[0] - 'A');
    lastans = pam.damage[pos[1]];
    printf("%d\n",lastans);
    int total = lastans;
    for (int i = 2;;i ++){
        int F;
        scanf("%d",&F);
        F ^= lastans;
        if (!F)break;
        scanf("%s",buf);
        a[i] = buf[0];
        sum[i] = sum[F] + score[buf[0]];
        st[i][0] = F;
        for (int step = 1;step < 20 and st[i][step-1];step ++){
            st[i][step] = st[st[i][step-1]][step-1];
        }
        pos[i] = pam.add(i,F,pos[F],buf[0] - 'A');
        Damage[i] = pam.damage_sum[pos[i]] % mod;
        (total += Damage[i]) %= mod;
        printf("%d\n",lastans = pam.damage[pos[i]]);
    }
    printf("%d\n",total);
    return 0;
}