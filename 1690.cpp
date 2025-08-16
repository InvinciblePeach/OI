#include <bits/stdc++.h>

using namespace std;

int n, dp[305][305];
string s;

int main(){
    cin >> s;
    s = " " + s;
    n = s.size();
    for (int i = 1; i <= n; i++){dp[i][i] = 1;}
    for (int len = 1; len <= n; len++){
        for (int l = 1; l <= n - len + 1; l++){
            int r = l + len - 1;
            for (int k = l; k <= r; k++){
                if (s[l] != s[r]){
                    dp[l][r] = 0;
                    break;
                }
                
            }
        }
    }
    return 0;
}