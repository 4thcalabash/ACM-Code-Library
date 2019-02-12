//
// Created by DELL on 2019/2/12.
//luogu 4777
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+100;
namespace CRT{
    ll ex_gcd(ll a,ll b,ll& x,ll& y){
        if (b == 0){x = 1;y = 0;return a;}
        ll gcd = ex_gcd(b,a%b,x,y);
        ll t = x;x = y;y = t - a/b*y;
        return gcd;
    }
    ll mul_mod(ll a,ll b,ll m){
        ll res = 0;
        while (b){
            if (b&1){
                res = (res + a) % m;
            }
            b >>=1;
            a = a * 2 % m;
        }
        return res;
    }
    // ans = first + t * second;
    // x = second (mod first)
    pair<ll,ll>work(vector<pair<ll,ll> >&es ){
        ll ans = es[0].second;
        ll M = es[0].first;
        for (int i=1;i<es.size();i++){
            ll a = es[i].first;
            ll b = es[i].second;
            ll x,y;
            ll gcd = ex_gcd(M,a,x,y);
            ll c = (b - ans %a + a) % a;
            a/=gcd;
            if (c % gcd)return {-1,-1};
            x = (mul_mod(x ,(c / gcd),a) + a)% a;
            ans += M * x;
            M *= a;
            ans %= M;
        }
        return {ans,M};
    }
}
vector<pair<ll,ll> > es;
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        ll a,b;
        scanf("%lld%lld",&a,&b);
        es.push_back(make_pair(a,b));
    }
    pair<ll,ll> ans = CRT::work(es);
   // cout<<ans.first<<" "<<ans.second<<endl;
    ll x = ans.first;
    cout<<x<<endl;
    return 0;
}
