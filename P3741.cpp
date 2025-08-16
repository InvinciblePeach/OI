#include <bits/stdc++.h>

using namespace std;

int n, ans = 0;
string s;

int main(){
    cin >> n >> s;
    for(int i = 0; i < n - 1; i++){
        if (s[i] == 'V' && s[i + 1] == 'K'){
            s[i] = 'a';
            s[i + 1] = 'b';
            ans ++;
        }
    }
    for (int i = 0; i < n - 1; i++){
        if (s[i] == s[i + 1]){
            ans ++;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
