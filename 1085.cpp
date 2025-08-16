#include <bits/stdc++.h>

using namespace std;

int k, n = 0;
string s;

int main(){
    cin >> k;
    for (int i = 1; i <= k; i++){
        cin >> s;
        n = s[s.size() - 1] - '0';
        if (s.size() >= 2){n += (s[s.size() - 2] - '0') * 10;}
        if (s.size() >= 3){n += (s[s.size() - 3] - '0') * 100;}
        n = n % 500;
        long long ans = 2011;
        for (int j = 1; j < n; j++){
            ans = ans * 2011 % 10000;
        }
        cout << ans << endl;
    }
    return 0;
}