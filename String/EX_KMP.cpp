// Created by calabash_boy on 2019/12/11.
// CF 1200E
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
//result: extend[i] = LCP(S[i,lens],T)
//require: nxt[i] = LCP(T[i,lent],T)
void exkmp(char *s,int lens,char *t,int lent,int *extend,int *nxt){
    extend[0] = 0;
    for (int i = 1,p0 = 0,p = 0;i <= lens;i ++){
        extend[i] = i <= p ? min(nxt[i - p0 + 1], p - i + 1) : 0;
        while (i + extend[i] <= lens and extend[i] < lent and s[i + extend[i]] == t[extend[i]+1])extend[i] ++;
        if (i + extend[i] - 1 >= p and i != 1)p0 = i,p = i + extend[i] - 1;
    }
}
char s[maxn],t[maxn];
int extend[maxn];
int nxt[maxn];
int main(){
    int n;
    scanf("%d",&n);
    int LEN = 0;
    for (int i=1;i<=n;i++){
        scanf("%s",t+1);
        int lent = strlen(t+1);
        int lens = min(LEN,lent);
        exkmp(t,lent,t,lent,nxt,nxt);
        exkmp(s + LEN - lens,lens,t,lent,extend,nxt);
        int sp = 0;
        for (int j = 1;j <= lens;j ++){
            if (lens - j + 1 == extend[j]){
                sp = extend[j];
                break;
            }
        }
        strcpy(s + LEN+1,t + sp + 1);
        LEN += lent - sp;
    }
    printf("%s\n",s+1);
    return 0;
}

