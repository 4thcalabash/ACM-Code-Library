/* x in [1,N]; y in [1,M] (x,y) = 1 */
#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 1e5+100;
typedef long long ll;
bool used[maxn];
vector<int> prime;
ll mu[maxn];
void sieve(){
    mu[1] = 1;
    for (int i=2;i<maxn;i++){
        if(!used[i]){
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0;j<prime.size();j++){
            long long nxt = 1ll* prime[j] * i;
            if(nxt >= maxn)break;
            used[nxt] = 1;
            if (i % prime[j] == 0){
                mu[nxt] = 0;
                break;
            }else{
                mu[nxt] = -mu[i];
            }
        }
    }
}
ll work(int n,int m){
    ll ans = 0;
    int top = min(n,m);
    for (int i=1;i<=top;i++){
        ans += 1ll * mu[i] * (n/i) * (m/i);
    }
    return ans;
}
int main(){
    sieve();
    int T;
    scanf("%d",&T);
    for (int Case = 1;Case <= T;Case ++){
        int a,b,n,m,k;
        scanf("%d%d%d%d%d",&a,&n,&b,&m,&k);
        if(k == 0){
            printf("Case %d: 0\n",Case);
            continue;
        }
        n/=k;
        m/=k;
        printf("Case %d: %lld\n",Case,work(n,m) - work(min(n,m),min(n,m))/2);
    }
    return 0;
}