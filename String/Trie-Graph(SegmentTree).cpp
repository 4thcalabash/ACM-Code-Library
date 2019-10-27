// Created by calabash_boy on 2019/10/27.
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int n;
int p[maxn], c[maxn];
struct Node{
    int lson,rson;
    int val;
    void init(){
        val = 0;
        lson = rson = -1;
    }
}nodes[maxn * 25];
int node_cnt = 1;
int build(int x,int l,int r){
    int now = node_cnt ++;
    nodes[now].init();
    if (l == r) return now;
    int mid = l + r >> 1;
    nodes[now].lson = build(x<<1,l,mid);
    nodes[now].rson = build(x<<1|1,mid+1,r);
    return now;
}
int update(int id,int l,int r,int pos,int val){
    int now = node_cnt ++;
    nodes[now] = nodes[id];
    if (l == r){
        nodes[now].val = val;
        return now;
    }
    int mid = l + r >> 1;
    if (pos <= mid)nodes[now].lson = update(nodes[id].lson,l,mid,pos,val);
    else nodes[now].rson = update(nodes[id].rson,mid+1,r,pos,val);
    return now;
}
int query(int id,int l,int r,int pos){
    if (l == r)return nodes[id].val;
    int mid = l + r >> 1;
    if (pos <= mid)return query(nodes[id].lson,l,mid,pos);
    else return query(nodes[id].rson,mid+1,r,pos);
}
struct Trie{
    map<int,int> nxt[maxn];
    int root[maxn], fail[maxn];
    int cnt = 1;
    int insert(int pre,int ch) {
        return nxt[pre].find(ch) == nxt[pre].end() ? nxt[pre][ch] = cnt++ : nxt[pre][ch];
    }
    void build(){
        queue<int> Q;Q.push(0);
        root[0] = ::build(1,1,n);
        for (auto edge : nxt[0]){
            int v,ch;
            tie(ch,v) = edge;
            root[0] = update(root[0],1,n,ch,v);
        }
        while (!Q.empty()){
            int head = Q.front();Q.pop();
            for (auto edge: nxt[head]){
                int v,ch;
                tie(ch,v) = edge;
                if (head == 0)fail[v] = 0;
                else fail[v] = query(root[fail[head]],1,n,ch);
                root[v] = root[fail[v]];
                for (auto edge2 : nxt[v]){
                    int v2,ch2;
                    tie(ch2,v2) = edge2;
                    root[v] = update(root[v],1,n,ch2,v2);
                }
                Q.push(v);
            }
        }
    }
}trie;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        scanf("%d",p+i);
    }
    for (int i=1;i<=n;i++){
        scanf("%d",c+i);
        trie.insert(p[i],c[i]);
    }
    trie.build();
    for (int i=1;i<=n;i++){
        cout<<trie.fail[i] <<" ";
    }
    cout<<endl;
    return 0;
}