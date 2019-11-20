// Created by calabash_boy on 19-11-20.
// CF 932G 偶回文分割方案数
// 优化DP转移：枚举所有回文后缀转移
// 使用时，只需要修改3行TBD
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e6+100;
struct Palindromic_AutoMaton{
    int s[maxn],now;
    int nxt[maxn][26],fail[maxn],l[maxn],last,tot;
    int diff[maxn],anc[maxn],g[maxn],f[maxn];
    void clear(){
        //1节点：奇数长度root 0节点：偶数长度root
        s[0] = l[1] = -1;
        fail[0] = tot = now =1;
        last = l[0] = 0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int len){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=0;l[tot]=len;
        return tot;
    }
    int get_fail(int x){
        while (s[now-l[x]-2]!=s[now-1])x = fail[x];
        return x;
    }
    void add(int ch){
        s[now++] = ch;
        int cur = get_fail(last);
        if(!nxt[cur][ch]){
            int tt = newnode(l[cur]+2);
            fail[tt] = nxt[get_fail(fail[cur])][ch];
            nxt[cur][ch] = tt;
            diff[tt] = l[tt] - l[fail[tt]];
            anc[tt] = diff[tt] == diff[fail[tt]]? anc[fail[tt]] : fail[tt];
        }
        last = nxt[cur][ch];
    }
    void trans(int i){
        for (int p = last;p>1;p = anc[p]){
            g[p] = f[i - l[anc[p]] - diff[p]];/*TBD*/
            if (diff[p] == diff[fail[p]]){
                (g[p] += g[fail[p]]) %= mod;/*TBD*/
            }
            (f[i] += (i % 2 == 0) *g[p]) %= mod;/*TBD*/
        }
    }
    int init(char* s){
        f[0] = 1;
        int n = strlen(s + 1);
        for (int i=1;i<=n;i++){
            add(s[i] - 'a');
            trans(i);
        }
        return f[n];
    }
}pam;
char t[maxn], s[maxn];
int main(){
    scanf("%s",s + 1);
    int n = strlen(s+1);
    for (int i=1;i<=n/2;i++){
        t[2 * i - 1] = s[i];
        t[2 * i] = s[n + 1- i ];
    }
    cout<<pam.init(t)<<endl;
    return 0;
}