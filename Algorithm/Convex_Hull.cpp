// Created by calabash_boy on 18-9-14.
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1005;
#define M_PI 3.1415926535
struct Node{int x,y;};
int st[maxn],top; Node a[maxn];
int rk[maxn];int n,T,l;
LL cross(const Node &a,const Node &b,const Node &c){
    return 1LL*(b.x-a.x)*(c.y-a.y)-1LL*(c.x-a.x)*(b.y-a.y);
}
LL cross(int x,int y,int z){return cross(a[x],a[y],a[z]);}
double dis(const Node &a,const Node &b){
    return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y));
}
bool cmp(int x,int y){
    LL m = cross(a[rk[0]],a[x],a[y]);
    if (m>0)return 1;
    else if (m==0&&dis(a[rk[0]],a[x])<=dis(a[rk[0]],a[y]))return 1;
    else return 0;
}
void solve(){
    scanf("%d%d",&n,&l);
    for (int i=0;i<n;i++){
        scanf("%d%d",&a[i].x,&a[i].y);
        rk[i]=i;
    }
    for (int i=1;i<n;i++){
        if (a[rk[i]].y<a[rk[0]].y||a[rk[i]].y==a[rk[0]].y&&a[rk[i]].x<a[rk[0]].x)swap(rk[i],rk[0]);
    }
    sort(rk+1,rk+n,cmp);top=2;
    st[0]=rk[0];st[1]=rk[1];
    for (int i=2;i<n;i++){
        while (cross(st[top-2],st[top-1],rk[i])<0)top--;
        st[top++] =rk[i];
    }
    double ans =0;
    for (int i=1;i<top;i++){ans+=dis(a[st[i]],a[st[i-1]]);}
    ans+=dis(a[st[0]],a[st[top-1]]);
    ans+=2*M_PI*l;
    printf("%.0lf\n",ans);
}
int main(){
    scanf("%d",&T);
    while (T--){
        solve();
        if (T!=0)printf("\n");
    }
    return 0;
}