#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+25;
int n,m,p,T,fac[N];
int qpow(int a,int b){
    int res = 1;
    while(b){
        if(b &1){
            res = (res * a %p);
        }
        a = a * a %p;
        b>>=1;
    }
    return res;
}
int inv(int a){
    return qpow(a,p-2);
}
int C(int a,int b){
    if(b > a)return 0;

}
int lucas(int a,int b){
    if(b == 0)return 1;
    return lucas(a/p,b/p) * C(a%p,b%p) %p;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> T;
    fac[0] = 1;
    for(int i =1;i<=N;i++){
        fac[i] = fac[i-1] * i % p;
    }
    while(T--){
        cin >> n >> m >> p;
        cout << lucas(n+m,n) << "\n";

    }

    return 0;
}


