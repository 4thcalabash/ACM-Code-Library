// Created by calabash_boy on 18-8-16.
#include<bits/stdc++.h>
#define FOR(i,l,r) for (int i = (l);i<(r);i++)
#define FORD(i,r,l) for (int i= (r);i>(l);i--)
using namespace std;
typedef long long LL;
typedef vector<LL> V;
const int MOD = 1e9+7;
// k 为 m 最高次数 且　a[m] == 1
namespace BerlekampMassey {
    inline void up(LL& a, LL b) { (a += b) %= MOD; }

    V mul(const V& a, const V& b, const V& m, int k) {
        V r; r.resize(2 * k - 1);
        FOR (i, 0, k)
            FOR (j, 0, k)
                up(r[i + j], a[i] * b[j]);
        FORD (i, k - 2, - 1) {
            FOR (j, 0, k)
                up(r[i + j], r[i + k] * m[j]);
            r.pop_back();
        }
        return r;
    }
    LL pow_mod (LL x,LL y){
        LL ret =1;
        for (;y;y>>=1){if (y&1) ret = ret*x%MOD;x = x * x %MOD;}
        return ret;
    }
    LL get_inv(LL x,LL MOD){
        return pow_mod(x,MOD-2);
    }
    V pow(LL n, const V& m) {
        int k = (int)m.size() - 1; assert(m[k] == -1 || m[k] == MOD - 1);
        V r(k), x(k); r[0] = x[1] = 1;
        for (; n; n >>= 1, x = mul(x, x, m, k))
            if (n & 1) r = mul(x, r, m, k);
        return r;
    }
    LL go(const V& a, const V& x, LL n) {
        // a: (-1, a1, a2, ..., ak).reverse
        // x: x1, x2, ..., xk
        // x[n] = sum[a[i]*x[n-i],{i,1,k}]
        int k = (int)a.size() - 1;
        if (n <= k) return x[n - 1];
        V r = pow(n - 1, a);
        LL ans = 0;
        FOR (i, 0, k)
            up(ans, r[i] * x[i]);
        return ans;
    }

    V BM(const V& x) {
        V a = {-1}, b = {233};
        FOR (i, 1, x.size()) {
            b.push_back(0);
            LL d = 0, la = a.size(), lb = b.size();
            FOR (j, 0, la) up(d, a[j] * x[i - la  + 1 + j]);
            if (d == 0) continue;
            V t; for (auto& v: b) t.push_back(d * v % MOD);
            FOR (j, 0, a.size()) up(t[lb - 1 - j], a[la - 1 - j]);
            if (lb > la) {
                b = a;
                LL inv = -get_inv(d, MOD);
                for (auto& v: b) v = v * inv % MOD;
            }
            a.swap(t);
        }
        for (auto& v: a) up(v, MOD);
        return a;
    }
    void sample();
}
void BerlekampMassey::sample(){
    V x(6);
    x[0] = 1;x[1] = 2;
    x[2] = 21;x[3] = 212;
    x[4] = 2141;x[5] = 21622;
    V a = BerlekampMassey::BM(x);
    cout<<"a[n] = ";
    for (int i = 0;i<a.size()-2;i++){
        cout<<a[i]<<"*a[n-"<<a.size()-1-i<<"] + ";
    }
    cout<<a[a.size()-2]<<"*a[n-1]"<<endl;
}
int main(){
    BerlekampMassey::sample();
    return 0;
}
