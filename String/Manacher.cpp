// Created by calabash_boy on 18-9-14.
#include<bits/stdc++.h>
using namespace std;
const int MAX = 2e5+10000;
char s[MAX];
struct Manacher{
    int lc[MAX];
    char ch[MAX];
    int N;
    Manacher(char *s){init(s);manacher();}
    /* s 1 bas */
    void init(char *s){
        int n = strlen(s+1);
        ch[n*2 +1] = '#';
        ch[0] = '@';
        ch[n*2 +2] = '\0';
        for (int i=n;i>=1;i--){
            ch[i*2] = s[i];ch[i*2 -1] = '#';
        }
        N = 2* n +1;
    }
    void manacher(){
        lc[1]=1;  int k=1;
        for (int i=2;i<=N;i++){
            int p = k+lc[k]-1;
            if (i<=p){
                lc[i]=min(lc[2*k-i],p-i+1);
            }else{  lc[i]=1;  }
            while (ch[i+lc[i]]==ch[i-lc[i]])lc[i]++;
            if (i+lc[i]>k+lc[k])k=i;
        }
    }
    void debug(){
        puts(ch);
        for (int i=1;i<=N;i++){
            printf("lc[%d]=%d\n",i,lc[i]);
        }
    }
};
int main(){
    scanf("%s",s+1);
    Manacher manacher(s);
    manacher.debug();
    return 0;
}