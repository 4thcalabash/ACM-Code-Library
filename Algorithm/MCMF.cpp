
// Created by calabash_boy on 19-10-5.
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3 * 250 + 100;
const int maxm = 2 * 250 * 250 + 100;
const int inf = 10000;
const int INF = 0x3f3f3f3f;
struct MCMF{
    int ss,tt,dis[maxn],pre[maxn];
    int first[maxn],from[maxm*2],des[maxm*2],nxt[maxm*2],cost[maxm*2],flow[maxm*2],tot;
    bool in[maxn];
    MCMF(){
        clear();
    }
    void clear(){
        tot =-1;
        memset(first,-1,sizeof first);
    }
    // <u,v,flow,cost>
    void init(vector<tuple<int,int,int,int> > E){
        for (auto edge : E){
            int u,v,f,c;
            tie(u,v,f,c) = edge;
            addEdge(u, v, f, c);
        }
    }
    void __addE(int x,int y,int f,int c){
        tot++;
        from[tot] =x;des[tot] =y;
        flow[tot] =f;cost[tot] =c;
        nxt[tot] = first[x];first[x] = tot;
    }
    inline void addEdge(int x,int y,int f,int c){
        __addE(x,y,f,c);__addE(y,x,0,-c);
    }
    bool spfa(){
        memset(in,0,sizeof in);
        for (int i=0;i<maxn;i++)dis[i] = INF;
        memset(pre,-1,sizeof pre);
        dis[ss] =0;in[ss] =1;
        queue<int> Q;Q.push(ss);
        while (!Q.empty()){
            int q = Q.front();
            Q.pop();in[q] = 0;
            for (int t = first[q];t!=-1;t = nxt[t]){
                int v=des[t],len=cost[t],cx=flow[t];
                if (cx&&dis[v]>dis[q]+len){
                    dis[v] = dis[q]+len;
                    pre[v] = t;
                    if (!in[v]){
                        Q.push(v);in[v] = 1;
                    }
                }
            }
        }
        // min cost max flow
        //return pre[tt] != -1;
        
        // min cost. flow needn't be max.
        return pre[tt]!=-1 && dis[tt] < 0;
    }
    // <flow,cost>
    pair<int,int> run(int s, int t){
        ss =s;tt=t;
        int totflow =0,totcost =0,nowflow =0,nowcost =0;
        while (spfa()){
            nowcost =0;nowflow = INF;
            int now =pre[tt];
            while (now!=-1){
                nowflow = min(nowflow,flow[now]);
                now = pre[from[now]];
            }
            now = pre[tt];
            while (now!=-1){
                flow[now] -= nowflow;
                flow[now^1] += nowflow;
                nowcost +=cost[now];
                now = pre[from[now]];
            }
            nowcost*=nowflow;
            totflow +=nowflow;
            totcost +=nowcost;
        }
        return make_pair(totflow,totcost);
    }
    // special
    void output(int cost);
}mcmf;
int n,m;
int a[maxn];
int id[maxn];
int argvalue[maxn];
vector<string> ans;
void copy(int argid,int val){
    stringstream stm;
    stm<<(char)('a' + argid - 1)<<"="<<val;
    ans.push_back(stm.str());
}
void print(int argid){
    stringstream stm;
    stm<<"print("<<(char)('a' + argid - 1)<<")";
    ans.push_back(stm.str());
}
void MCMF::output(int cost){
    int argid = 0;
    for (int i=1;i<=n;i++){
        int A = 2 * i-1;
        int B = 2 * i;
        if (id[A] == 0){
            argid ++;
            id[A] = argid;
            copy(argid, a[i]);
            print(argid);
            argvalue[argid] = a[i];
        }else{
            int temp_value = argvalue[id[A]];
            if (temp_value != a[i]){
                copy(id[A], a[i]);
                argvalue[id[A]] = a[i];
            }
            print(id[A]);
        }
        for (int t = first[B];t != -1;t = nxt[t]){
            int v = des[t];
            int f = flow[t];
            if (f|| v == A){
                continue;
            }
            if (v == 2 * n + 3) break;
            else{
                id[v] = id[A];
            }
        }
    }
    cout<<ans.size()<<" "<<cost<<endl;
    for (auto str : ans){
        cout<<str<<endl;
    }
}
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<tuple<int,int,int,int> > E(0);
    int SS = 2 * n + 1;
    int S = 2 * n + 2;
    int T = 2 * n + 3;
    E.push_back(make_tuple(SS,S,m,0));
    for (int i=1;i<=n;i++){
        int A = 2 * i - 1;
        int B = 2 * i;
        E.push_back(make_tuple(A,B,1,-inf));
        E.push_back(make_tuple(S,A,1,__builtin_popcount(a[i])));
        E.push_back(make_tuple(B,T,1,0));
        for (int j=i+1;j<=n;j++){
            int AA = 2 * j - 1;
            int BB = 2 * j;
            if (a[i] == a[j]){
                E.push_back(make_tuple(B,AA,1,0));
            }else{
                E.push_back(make_tuple(B,AA,1,__builtin_popcount(a[j])));
            }
        }
    }
    mcmf.init(E);
    pair<int,int> ans = mcmf.run(SS, T);
    //cerr<<ans.first<<","<<ans.second<<endl;
    mcmf.output((ans.second% inf + inf) % inf);
    return 0;
}
