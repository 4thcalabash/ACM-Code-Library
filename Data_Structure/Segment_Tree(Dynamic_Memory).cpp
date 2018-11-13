// Created by calabash_boy on 18-10-1.
// CF 1046A
// give n tuple(x,r,p) and k<=20 , calc unordered pair(i,j)
// xi - ri <= xj <= xi + ri
// xj - rj <= xi <= xj + rj
// |pi - pj| <=k
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
typedef long long ll;
struct Node{ int L,R,val; }tree[maxn*200];
int cnt;
struct Segment_Tree{
    int root = 0;
    int newnode(){
        ++cnt;
        tree[cnt].val = tree[cnt].L = tree[cnt].R = 0;
        return cnt;
    }
    Segment_Tree(){ root = newnode(); }
    void add(int x,int l,int r,int Pos,int delta){
        tree[x].val += delta;
        if (l == r)return;
        int mid = l+r >>1;
        if (Pos <= mid){
            if (tree[x].L == 0){
                tree[x].L = newnode();
            }
            add(tree[x].L,l,mid,Pos,delta);
        }else{
            if (tree[x].R == 0){
                tree[x].R = newnode();
            }
            add(tree[x].R,mid+1,r,Pos,delta);
        }
    }
    int query(int x,int l,int r,int L,int R){
        if (!x)return 0;
        if (l>R || L>r)return 0;
        if (L <= l && r <= R)return tree[x].val;
        int mid = l+r >>1;
        return query(tree[x].L,l,mid,L,R) + query(tree[x].R,mid+1,r,L,R);
    }
};
map<int,Segment_Tree> mp;
map<int,int> id;
int N;
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    vector<tuple<int,int,int> > a(n);
    vector<int> nums;
    for (int i=0;i<n;i++){
        int x,r,q;scanf("%d%d%d",&x,&r,&q);
        a[i] = make_tuple(x,r,q);
        nums.push_back(x);
        nums.push_back(x+r);
        nums.push_back(x-r);
    }
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    for (int i=0;i<nums.size();i++){
        id[nums[i]] = i+1;
    }
    N = nums.size();
    sort(a.begin(),a.end(),[](const tuple<int,int,int> &a,const tuple<int,int,int>&b){
        return get<1>(a) > get<1>(b);
    });
    ll ans =0;
    for (int i=0;i<n;i++){
        int x,r,q;tie(x,r,q) = a[i];
        int L = id[x-r],R = id[x+r];
        for (int j=q-k;j<=q+k;j++){
            if (mp.find(j) == mp.end())continue;
            Segment_Tree & tree = mp[j];
            int root = tree.root;
            ans += tree.query(root,1,N,L,R);
        }
        Segment_Tree & tree = mp[q];
        int root = tree.root;
        tree.add(root,1,N,id[x],1);
    }
    cout<<ans<<endl;
    return 0;
}