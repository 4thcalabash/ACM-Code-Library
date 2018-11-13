// Created by calabash_boy on 18-9-14.
#include<bits/stdc++.h>
using namespace std;
const int MAX = 2e5+10000;
char ch[MAX];
int lc[MAX],n;
void Manacher(){
    lc[1]=1;  int k=1;
    for (int i=2;i<=n;i++){
        int p = k+lc[k]-1;
        if (i<=p){
            lc[i]=min(lc[2*k-i],p-i+1);
        }else{  lc[i]=1;  }
        while (ch[i+lc[i]]==ch[i-lc[i]])lc[i]++;
        if (i+lc[i]>k+lc[k])k=i;
    }
}
void debug(){
    for (int i=1;i<=n;i++){
        printf("lc[%d]=%d\n",i,lc[i]);
    }
}
int main(){
    scanf("%s",ch+1);
    //calc n must before call Manacher
    n = strlen(ch+1);
    ch[n*2+1] = '#';
    for (int i=n;i>=1;i--){
        ch[i*2] = ch[i];ch[i*2-1] = '#';
    }
    n = n*2 +1;
    ch[0] = 'z'+1;ch[n+1] = '\0';
    Manacher();
    debug();
    return 0;
}