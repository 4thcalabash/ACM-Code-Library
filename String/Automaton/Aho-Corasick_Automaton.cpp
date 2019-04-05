// Created by calabash_boy on 18-6-5.
// HDU 6138
//给定若干字典串。
// query:strx stry 求最长的p,p为strx、stry子串，且p为某字典串的前缀
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
struct Aho_Corasick_Automaton{
    //basic
    int nxt[maxn*10][26],fail[maxn*10];
    int root,tot;
    //special
    int flag[maxn*10];
    int len[maxn*10];
    void clear(){
        memset(nxt[0],0,sizeof nxt[0]);
        root = tot=0;
    }
    int newnode(){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        flag[tot] = len[tot]=0;
        return tot;
    }
    void insert(char *s ){
        int now = root;
        while (*s){
            int id = *s-'a';
            if(!nxt[now][id])nxt[now][id] = newnode();
            len[nxt[now][id]] = len[now]+1;
            now = nxt[now][id];
        }
    }
    void insert(string str){
        int now = root;
        for (int i=0;i<str.size();i++){
            int id = str[i]-'a';
            if(!nxt[now][id])nxt[now][id] = newnode();
            len[nxt[now][id]] = len[now]+1;
            now = nxt[now][id];
        }
    }
    void build(){
        fail[root] = root;
        queue<int>Q;Q.push(root);
        while (!Q.empty()){
            int head = Q.front();Q.pop();
            for (int i=0;i<26;i++){
                if(!nxt[head][i])continue;
                int temp = nxt[head][i];
                fail[temp] = fail[head];
                while (fail[temp]&&!nxt[fail[temp]][i]){
                    fail[temp] = fail[fail[temp]];
                }
                if(head&&nxt[fail[temp]][i])fail[temp] = nxt[fail[temp]][i];
                Q.push(temp);
            }
        }
    }
    void search(string str,int QID);
    int query(string str,int QID);
}acam;
void Aho_Corasick_Automaton::search(string str,int QID) {
    int now = root;
    for (int i=0;i<str.size();i++){
        int id = str[i]-'a';
        now = nxt[now][id];int temp = now;
        while (temp!=root&&flag[temp]!=QID){
            flag[temp] = QID;
            temp = fail[temp];
        }
    }
}
int Aho_Corasick_Automaton::query(string str, int QID) {
    int ans =0;int now = root;
    for (int i=0;i<str.size();i++){
        int id = str[i]-'a';
        now = nxt[now][id];
        int temp = now;
        while (temp!=root){
            if(flag[temp]==QID){
                ans = max(ans,len[temp]);
                break;
            }
            temp = fail[temp];
        }
    }
    return ans;
}
string a[maxn];
int m,n,qid;
int main(){
    int T;cin>>T;
    while (T--){
        acam.clear();cin>>n;
        for (int i=1;i<=n;i++){
            cin>>a[i];
            acam.insert(a[i]);
        }
        acam.build();cin>>m;
        for (int i=1;i<=m;i++){
            int x,y;cin>>x>>y;
            qid++;
            acam.search(a[x],qid);
            int ans = acam.query(a[y],qid);
            cout<<ans<<endl;
        }
    }
    return 0;
}