//
// Created by calabash_boy on 18-7-3.
//
#include<bits/stdc++.h>
#define rank rkrk
using namespace std;
typedef long long ll;
const int maxn=1e5+100;
char ch[maxn];
struct Node{
    int val,index;
    Node(int val_,int index_):val(val_),index(index_){}
    bool operator < (const Node b)const{
        if (val==b.val)return b.index<index;
        return b.val<val;
    }
};
priority_queue<Node>pq;
namespace Suffix_Array{
    int cntA[maxn],cntB[maxn],tsa[maxn],A[maxn],B[maxn];
    int sa[maxn],rank[maxn],height[maxn];
    void GetSa(char *ch,int n){
        for(int i=0;i<maxn;i++)  cntA[i]=0;
        for(int i=1;i<=n;i++)   cntA[ch[i]]++;
        for(int i=1;i<=maxn;i++) cntA[i]+=cntA[i-1];
        for(int i=n;i;i--)  sa[cntA[ch[i]]--]=i;
        rank[sa[1]]=1;
        for(int i=2;i<=n;i++){
            rank[sa[i]]=rank[sa[i-1]];
            if(ch[sa[i]]!=ch[sa[i-1]])  rank[sa[i]]++;
        }
        for(int l=1;rank[sa[n]]<n;l<<=1){
            for(int i=0;i<maxn;i++)  cntA[i]=0;
            for(int i=0;i<maxn;i++)  cntB[i]=0;
            for(int i=1;i<=n;i++){
                cntA[A[i]=rank[i]]++;
                cntB[B[i]=(i+l<=n)?rank[i+l]:0]++;
            }
            for(int i=1;i<maxn;i++)   cntB[i]+=cntB[i-1];
            for(int i=n;i;i--)  tsa[cntB[B[i]]--]=i;
            for(int i=1;i<maxn;i++)  cntA[i]+=cntA[i-1];
            for(int i=n;i;i--)  sa[cntA[A[tsa[i]]]--]=tsa[i];
            rank[sa[1]]=1;
            for(int i=2;i<=n;i++){
                rank[sa[i]]=rank[sa[i-1]];
                if(A[sa[i]]!=A[sa[i-1]] || B[sa[i]]!=B[sa[i-1]])    rank[sa[i]]++;
            }
        }
    }
    void GetHeight(char *ch,int n){
        GetSa(ch,n);
        for(int i=1,j=0;i<=n;i++){
            if(j)   j--;
            while(ch[i+j]==ch[sa[rank[i]-1]+j]) j++;
            height[rank[i]]=j;
        }
    }
    //special
    int GetK(int k,int n){
        int ans=0;
        k--;
        if(k==0){
            for(int i=1;i<=n;++i)   ans=ans+(n-sa[i]+1-height[i]);
            return ans;
        }
        while (!pq.empty())pq.pop();
        for (int i=2;i<=n;i++){
            while (!pq.empty()&&pq.top().index<i-k+1)pq.pop();
            pq.push(Node(height[i],i));
            if (i>k){
                int top = pq.top().val;
                int last = height[i-k];
                ans +=max(0,top-last);
            }
        }
        return ans;
    }
};
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,k;
        scanf("%d",&k);
        scanf("%s",ch+1);
        n=strlen(ch+1);
        Suffix_Array::GetHeight(ch,n);
        printf("%d\n",Suffix_Array::GetK(k,n)-Suffix_Array::GetK(k+1,n));
    }
    return 0;
}

