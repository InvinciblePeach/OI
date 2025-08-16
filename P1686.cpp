#include <bits/stdc++.h>

using namespace std;

int ans = 0, l = INT_MAX, r = 0;
char way;
string s;

int main(){
    cin >> s;
    for (int i = 0; i < s.size(); i++){
        for (int j = i; j < s.size(); j++){
            if (s[i] == 'W' && s[j] == 'E'){
                if (ans >= j - i){
                    ans = j - i;
                    if (l > i){
                        l = i, r = j;
                    }
                    if (l == i){
                        r = max(r, j);
                    }
                }
                break;
            }
            if (s[i] == 'E' && s[j] == 'W'){
                if (ans >= j - i){
                    ans = j - i;
                    if (l > i){
                        l = i, r = j;
                    }
                    if (l == i){
                        r = max(r, j);
                    }
                }
                break;
            }
            if (s[i] == 'N' && s[j] == 'S'){
                if (ans >= j - i){
                    ans = j - i;
                    if (l > i){
                        l = i, r = j;
                    }
                    if (l == i){
                        r = max(r, j);
                    }
                }
                break;
            }
            if (s[i] == 'S' && s[j] == 'N'){
                if (ans >= j - i){
                    ans = j - i;
                    if (l > i){
                        l = i, r = j;
                    }
                    if (l == i){
                        r = max(r, j);
                    }
                }
                break;
            }
        }
    }

    cout << ans << ' ' << l << ' ' << r << endl;

    return 0;
}