// Created by calabash_boy on 18-10-6.
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e5+100;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int m,n;
const int demension = 2;
struct Hotel{
    int pos[demension],id,c;
}hotel[maxn],kdtree[maxn];
double var[demension];
int split [maxn];int cmpDem;
bool cmp(const Hotel &a,const Hotel &b){
    return a.pos[cmpDem]<b.pos[cmpDem];
}
void build (int l,int r){
    if (l>=r)return;
    int mid = l+r >>1;
    for (int i=0;i<demension;i++){
        double ave =0;
        for (int j=l;j<=r;j++){
            ave+=hotel[j].pos[i];
        }
        ave/=(r-l+1);var[i] =0;
        for (int j=l;j<=r;j++){
            var[i]+=pow(hotel[j].pos[i]-ave,2);
        }
        var[i]/=(r-l+1);
    }
    split[mid] =-1;double maxVar=-1;
    for (int i=0;i<demension;i++){
        if (var[i]>maxVar){
            maxVar = var[i];
            split[mid] =i;
        }
    }
    cmpDem = split[mid];
    nth_element(hotel+l,hotel+mid,hotel+r+1,cmp);
    build (l,mid-1);build (mid+1,r);
}
int ansIndex;
LL ansDis;
void query(int l,int r,const Hotel& x){
    if (l>r)return ;
    int mid = l+r >>1;LL dis =0;
    for (int i=0;i<demension;i++){
        dis +=1LL*(x.pos[i]-hotel[mid].pos[i])*(x.pos[i]-hotel[mid].pos[i]);
    }
    if (hotel[mid].c<=x.c){
        if (ansDis == dis && hotel[mid].id<hotel[ansIndex].id){
            ansIndex = mid;
        }else if (dis<ansDis){
            ansDis = dis;
            ansIndex = mid;
        }
    }
    int d = split[mid];
    LL radius = 1LL*(x.pos[d]-hotel[mid].pos[d])*(x.pos[d]-hotel[mid].pos[d]);
    if (x.pos[d]<hotel[mid].pos[d]){
        query(l,mid-1,x);
        if (ansDis>radius){query(mid+1,r,x);}
    }else{
        query(mid+1,r,x);
        if (ansDis>radius){query(l,mid-1,x);}
    }
}
int T;
void input(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++){
        scanf("%d%d%d",&hotel[i].pos[0],&hotel[i].pos[1],&hotel[i].c);
        hotel[i].id=i;
    }
    build (0,n-1);
}
void solve(){
    Hotel x;
    for (int i=1;i<=m;i++){
        scanf("%d%d%d",&x.pos[0],&x.pos[1],&x.c);
        ansDis = INF;ansIndex =n+1;
        query(0,n-1,x);
        printf("%d %d %d\n",hotel[ansIndex].pos[0],hotel[ansIndex].pos[1],hotel[ansIndex].c);
    }
}
int main(){
    scanf("%d",&T);
    while (T--){
        input();
        solve();
    }
    return 0;
}