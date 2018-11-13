// Created by calabash_boy on 18-6-18.
#include <bits/stdc++.h>
using namespace std;
namespace fft {
    //attention data type
    typedef long long type;
    typedef double db;
    struct cp {
        db x, y;
        cp() { x = y = 0; }
        cp(db x, db y) : x(x), y(y) {}
    };
    cp operator+(cp a, cp b) { return cp(a.x + b.x, a.y + b.y); }
    cp operator-(cp a, cp b) { return cp(a.x - b.x, a.y - b.y); }
    cp operator*(cp a, cp b) { return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    cp conj(cp a) { return cp(a.x, -a.y); }
    type base = 1;
    vector<cp> roots = {{0, 0}, {1, 0}};
    vector<type> rev = {0, 1};
    const db PI = acosl(-1.0);
    void ensure_base(type nbase) {
        if (nbase <= base) return;
        rev.resize(static_cast<unsigned long>(1 << nbase));
        for (type i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        roots.resize(static_cast<unsigned long>(1 << nbase));
        while (base < nbase) {
            db angle = 2 * PI / (1 << (base + 1));
            for (type i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                db angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = cp(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }
    void fft(vector<cp> &a, type n = -1) {
        if (n == -1) n = a.size();
        assert((n & (n - 1)) == 0);
        type zeros = __builtin_ctz(n);
        ensure_base(zeros);
        type shift = base - zeros;
        for (type i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (type k = 1; k < n; k <<= 1) {
            for (type i = 0; i < n; i += 2 * k) {
                for (type j = 0; j < k; j++) {
                    cp z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }
    vector<cp> fa, fb;
    vector<type> multiply(vector<type> &a, vector<type> &b) {
        type need = a.size() + b.size() - 1;
        type nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        type sz = 1 << nbase;
        if (sz > (type) fa.size())
            fa.resize(static_cast<unsigned long>(sz));
        for (type i = 0; i < sz; i++) {
            type x = (i < (type) a.size() ? a[i] : 0);
            type y = (i < (type) b.size() ? b[i] : 0);
            fa[i] = cp(x, y);
        }
        fft(fa, sz);
        cp r(0, -0.25 / sz);
        for (type i = 0; i <= (sz >> 1); i++) {
            type j = (sz - i) & (sz - 1);
            cp z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            if (i != j) {
                fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            }
            fa[i] = z;
        }
        fft(fa, sz);
        vector<type> res(static_cast<unsigned long>(need));
        for (type i = 0; i < need; i++) {
            res[i] = fa[i].x + 0.5;
        }
        return res;
    }
    vector<type> multiply_mod(vector<type> &a, vector<type> &b, type m, type eq = 0) {
        type need = a.size() + b.size() - 1;
        type nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        type sz = 1 << nbase;
        if (sz > (type) fa.size()) {
            fa.resize(static_cast<unsigned long>(sz));
        }
        for (type i = 0; i < (type) a.size(); i++) {
            type x = (a[i] % m + m) % m;
            fa[i] = cp(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, cp {0, 0});
        fft(fa, sz);
        if (sz > (type) fb.size()) {
            fb.resize(static_cast<unsigned long>(sz));
        }
        if (eq) {
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        } else {
            for (type i = 0; i < (type) b.size(); i++) {
                type x = (b[i] % m + m) % m;
                fb[i] = cp(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, cp {0, 0});
            fft(fb, sz);
        }
        db ratio = 0.25 / sz;
        cp r2(0, -1);cp r3(ratio, 0);
        cp r4(0, -ratio);cp r5(0, 1);
        for (type i = 0; i <= (sz >> 1); i++) {
            type j = (sz - i) & (sz - 1);
            cp a1 = (fa[i] + conj(fa[j]));
            cp a2 = (fa[i] - conj(fa[j])) * r2;
            cp b1 = (fb[i] + conj(fb[j])) * r3;
            cp b2 = (fb[i] - conj(fb[j])) * r4;
            if (i != j) {
                cp c1 = (fa[j] + conj(fa[i]));
                cp c2 = (fa[j] - conj(fa[i])) * r2;
                cp d1 = (fb[j] + conj(fb[i])) * r3;
                cp d2 = (fb[j] - conj(fb[i])) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);fft(fb, sz);
        vector<type> res(static_cast<unsigned long>(need));
        for (type i = 0; i < need; i++) {
            long long aa = fa[i].x + 0.5;
            long long bb = fb[i].x + 0.5;
            long long cc = fa[i].y + 0.5;
            res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
        }
        return res;
    }
    vector<type> square_mod(vector<type> &a, type m) {
        return multiply_mod(a, a, m, 1);
    }
};
const int maxn = 2e5+100;
int n,x;
int a[maxn],sum[maxn],cnt[maxn];
vector<long long > A,B,C;
//example:
//f[i] = number of subsequences whose occurence of 1 is i.
//f[i] = \sum_{cnt[j]*cnt[j-i]}
int main(){
    scanf("%d%d",&n,&x);cnt[0]=1;
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        sum[i] =sum[i-1];
        if(a[i]<x)sum[i]++;
        cnt[sum[i]]++;
    }
    A.resize(n*2+2);B.resize(n*2+2);
    for (int i=0;i<=n;i++){
        A[n+i] = cnt[i];B[n-i] = cnt[i];
    }
    C = fft::multiply(A,B);
    C[n*2]-=n+1;C[n*2]>>=1;
    for (int i=n*2;i<=n*3;i++){ cout<<C[i]<<" "; }
    return 0;
}