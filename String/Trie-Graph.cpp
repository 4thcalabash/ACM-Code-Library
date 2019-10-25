// Created by calabash_boy on 2019/10/25.
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
struct Trie {
    int nxt[maxn][26], fail[maxn];
    // the node I should go when append a character
    int Go[maxn][26];
    int root = 0;
    int cnt = 0;
    void clear(){
        root = cnt = 0;
        memset(nxt[0],0,sizeof nxt[0]);
    }
    int newnode() {
        cnt++;
        //clear memory
        return cnt;
    }
    void insert(char *s) {
        int now = root;
        while (*s){
            now = insert(now,*s - 'a');
            s ++;
        }
    }
    int insert(int pre, int ch) {
        return nxt[pre][ch]?nxt[pre][ch] : nxt[pre][ch] = newnode();
    }
    void build() {
        queue<int> Q;
        Q.push(0);
        memcpy(Go[0],nxt[0],sizeof nxt[0]);
        while (!Q.empty()) {
            int head = Q.front();
            Q.pop();
            for (int ch = 0; ch < 26; ch++) {
                int v = nxt[head][ch];
                if (!v)continue;
                if (head == 0) fail[v] = 0;
                else fail[v] = Go[fail[head]][ch];
                memcpy(Go[v],Go[fail[v]],sizeof Go[v]);
                for (int cc = 0; cc < 26; cc++) {
                    if (nxt[v][cc])Go[v][cc] = nxt[v][cc];
                }
                Q.push(v);
            }
        }
    }
}trie;
